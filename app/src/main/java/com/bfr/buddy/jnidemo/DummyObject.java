package com.bfr.buddy.jnidemo;

public class DummyObject extends DisposableWithId {

    public DummyObject(int pId) {
        super(pId);
    }

    @Override
    native void disposeImplementation(int id);
}