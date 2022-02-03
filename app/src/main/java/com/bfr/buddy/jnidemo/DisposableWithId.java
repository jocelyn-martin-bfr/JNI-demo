package com.bfr.buddy.jnidemo;

public abstract class DisposableWithId {

    private final int id;
    private boolean isDisposed = false;

    protected DisposableWithId(int pId) {
        id = pId;
    }

    boolean getIsDisposed() {
        return isDisposed;
    }

    int getId() {
        return id;
    }

    public void dispose() {
        if (!isDisposed) {
            disposeImplementation();
            isDisposed = true;
        }
    }

    abstract void disposeImplementation();
}