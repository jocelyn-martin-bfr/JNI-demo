package com.bfr.buddy.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("demo-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn).setOnClickListener(v -> onButtonClick());
    }

    private void onButtonClick() {
        String textToPrint = new String();
        textToPrint += returnFortyTwo() + "\n";

        TextView textView = findViewById(R.id.textview);
        textView.setText(textToPrint);
    }

    native public int returnFortyTwo();
}