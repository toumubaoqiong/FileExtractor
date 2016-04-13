# FileExtractor
调用jni解压常用压缩格式的文件
# Before Build
由于jni是从eclipse项目中导入过来的，所以需要进行下配置：
<div>1、在build.gradle的android中加入一下代码：</div>
<div>
	<pre code_snippet_id="1646367" snippet_file_name="blog_20160413_1_7584301" name="code" class="java"> sourceSets {
        main {
            jniLibs.srcDirs = ['src/main/libs']
        }
    }</pre>
	<br />
	
</div>
2、android studio编译android.mk需要进行一下配置
<div>
	<pre code_snippet_id="1646367" snippet_file_name="blog_20160413_2_7267873" name="code" class="java">tasks.withType(JavaCompile) {
    compileTask -&gt; compileTask.dependsOn ndkBuild
}

task ndkBuild(type: Exec) {
    workingDir file('src/main/jni')
    commandLine getNdkBuildCmd()
}

task cleanNative(type: Exec){
    workingDir file('src/main/jni')
    commandLine getNdkBuildCmd(), 'clean'
}

clean.dependsOn cleanNative

def getNdkDir() {
    if (System.env.ANDROID_NDK_ROOT != null)
        return System.env.ANDROID_NDK_ROOT
    Properties properties = new Properties()
    properties.load(project.rootProject.file('local.properties').newDataInputStream())
    def ndkdir = properties.getProperty('ndk.dir', null)
    if (ndkdir == null)
        throw new GradleException(&quot;NDK location not found. Define location with ndk.dir in the local.properties file or with an ANDROID_NDK_ROOT environment variable.&quot;)
    return ndkdir
}

def getNdkBuildCmd() {
    def ndkbuild = getNdkDir() + &quot;/ndk-build&quot;
    ndkbuild += &quot;.cmd&quot;
    return ndkbuild
}</pre>
	<div>
		<br />
		
	</div>
	<span style="color:rgb(63,63,63); font-size:14px; line-height:30px">加入这些任务之后，编译流程变成了，clean操作之前会先执行ndk-build&nbsp;clean任务，编译动作之前会先执行ndk-build任务，这样就确保了编译执行gradle&nbsp;clean的时候回执行ndk-build&nbsp;clean操作，在编译开始之前执行ndk-build操作，确保所有的动态库都已经编译出来，而且在目录src/main/libs中，然后在编译apk的时候，直接使用src/main/libs中的动态库进行打包。</span>
</div>
<div>
	<span style="color:#3f3f3f"><span style="font-size:14px; line-height:30px"><br />
	</span></span>
</div>
