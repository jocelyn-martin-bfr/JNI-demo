package com.bfr.buddy.jnidemo;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class DummyData {

    public int i;
    public String str;
    public ExampleOfEnum exampleOfEnum;

    public DummyData(int pI, String pStr, ExampleOfEnum pExampleOfEnum) {
        i = pI;
        str = pStr;
        exampleOfEnum = pExampleOfEnum;
    }

    int getI() {
        return i;
    }

    String getStr() {
        return str;
    }

    ExampleOfEnum getExampleOfEnum() {
        return exampleOfEnum;
    }
}