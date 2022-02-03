package com.bfr.buddy.jnidemo;

public class DummyObject extends DisposableWithId {

    // To Force the construction to come from Cpp.
    // Because on Cpp side we don't care about public / protected / private.
    private DummyObject(int pId) {
        super(pId);
    }

    @Override
    native void disposeImplementation();
}