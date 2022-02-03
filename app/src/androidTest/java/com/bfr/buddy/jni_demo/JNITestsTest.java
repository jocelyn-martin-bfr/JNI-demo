package com.bfr.buddy.jni_demo;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

import com.bfr.buddy.jnidemo.DummyData;
import com.bfr.buddy.jnidemo.DummyObject;
import com.bfr.buddy.jnidemo.ExampleOfEnum;
import com.bfr.buddy.jnidemo.MainActivity;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class JNITestsTest {

    @Test
    public void test_returnFortyTwo() {
        assertEquals(42, MainActivity.returnFortyTwo());
    }

    @Test
    public void test_addFortyTwo() {
        assertEquals(43, MainActivity.addFortyTwo(1));
    }

    @Test
    public void test_returnString() {
        assertEquals("love", MainActivity.returnString());
    }

    @Test
    public void test_returnStringArray() {
        String[] strs = MainActivity.returnStringArray();
        assertEquals(2, strs.length);
        assertEquals("titi", strs[0]);
        assertEquals("toto", strs[1]);
    }

    @Test
    public void test_readCustomData() {
        DummyData dummyData = MainActivity.readCustomData(new DummyData(2, "val_str", ExampleOfEnum.VALUE_2));
        assertEquals(3, dummyData.i);
        assertEquals("val_str_cpp_addition", dummyData.str);
        assertEquals(ExampleOfEnum.VALUE_2, dummyData.exampleOfEnum);
    }

    @Test
    public void test_throwFromCpp() {
        try {
            MainActivity.throwFromCpp();
            fail("MainActivity.throwFromCpp(); did not throw");
        } catch (Exception e) {
            assertEquals("Cpp exception!", e.getMessage());
        }
    }

    @Test
    public void test_throwFromCppWithReturn() {
        assertEquals(46, MainActivity.throwFromCppWithReturn(45));

        try {
            MainActivity.throwFromCppWithReturn(-1);
            fail("MainActivity.throwFromCppWithReturn(); did not throw");
        } catch (Exception e) {
            assertEquals("Value must not be negative", e.getMessage());
        }
    }


    @Test
    public void test_syncObjectLivingBothInCppAndJavaWorld() {

        // Create Cpp and Java associated object
        DummyObject dummyObject = MainActivity.createCustomObject(48);

        // Use Cpp algorithm and data
        assertEquals(48, MainActivity.getValueStoredInCppSideOfDummyObject(dummyObject));

        // Release the Cpp memory associated to the object
        dummyObject.dispose();
    }
}