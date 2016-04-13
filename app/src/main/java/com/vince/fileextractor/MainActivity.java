package com.vince.fileextractor;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

    private String path;
    MyHandler handler = new MyHandler();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        path = Environment.getExternalStorageDirectory().getPath();
    }

    public void onClick(View v){
        final Message msg = handler.obtainMessage();
        new Thread(){
            @Override
            public void run() {
                super.run();
                //zip/rar/7z
                if(FileExtractor.fileExtractor(path + "/services.rar", path + "/")){
                    msg.what = 1;
                }else {
                    msg.what = 0;
                }
                msg.sendToTarget();
            }
        }.start();

    }

    class MyHandler extends Handler{
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            if(msg.what == 1){
                Toast.makeText(getApplicationContext(), "解压成功", Toast.LENGTH_LONG).show();
            }else{
                Toast.makeText(getApplicationContext(), "解压失败", Toast.LENGTH_LONG).show();
            }
        }
    }
}
