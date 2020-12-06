#pragma once

// Open Hash node class template
template <typename K, typename V>
class OpenHashNode
{
private:
    K _key;
    V _value;
    OpenHashNode(const HashNode&);
    OpenHashNode& operator=(const OpenHashNode&);

public:
    OpenHashNode(const K& key, const V& value) :
        _key(key), _value(value)
    {
    }
    K getKey() const
    {
        return _key;
    }

    V getValue() const
    {
        return _value;
    }

    void setValue(V value)
    {
        _value = value;
    }

    void setKey(K key)
    {
        _key = key;
    }
};
