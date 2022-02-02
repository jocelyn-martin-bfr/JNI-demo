package com.bfr.buddy.jnidemo;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class DummyData {

    public int i;
    public String str;

    public DummyData(int pI, String pStr) {
        i = pI;
        str = pStr;
    }

    int getI() {
        return i;
    }

    String getStr() {
        return str;
    }
}