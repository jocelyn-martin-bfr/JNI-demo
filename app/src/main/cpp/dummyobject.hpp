#ifndef JNIDEMO_DUMMYOBJECT_HPP
#define JNIDEMO_DUMMYOBJECT_HPP

class DummyObject
{
public:
    void load(int pValue) {
        value = std::make_unique<int>(pValue);
    }

    void unload() {
        value.reset();
    }

    int getValue() {
        if (!value)
            throw std::runtime_error("Dummy object is not loaded");
        return *value;
    }

private:
    std::unique_ptr<int> value; // simulate potentially big data
};

#endif // JNIDEMO_DUMMYOBJECT_HPP
