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
        String textToPrint = returnString();

        TextView textView = findViewById(R.id.textview);
        textView.setText(textToPrint);
    }

    // Example of a function returning an int
    static native public int returnFortyTwo();

    // Example of a function taking a string in parameter
    static native public int addFortyTwo(int value);

    // Example of a function returning a string
    static native public String returnString();

    // Example of a function returning a string array
    static native public String[] returnStringArray();

    // Example a function take a custom class in parameter
    static native public DummyData readCustomData(DummyData dummyData);

    // Example of a function throwing from Cpp
    static native public void throwFromCpp();

    // Example of a function throwing from Cpp and returning a value
    static native public int throwFromCppWithReturn(int value);

    // Example of a Cpp function creating a Java object/
    // The Java object has an associated Cpp object for the data that stay on a Cpp side.
    static native public DummyObject createCustomObject(int value);

    // Example of a function using Cpp algorithm and associated data to produce a result.
    static native public int getValueStoredInCppSideOfDummyObject(DummyObject dummyObject);
}