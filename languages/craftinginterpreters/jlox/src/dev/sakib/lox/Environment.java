package dev.sakib.lox;

import java.util.ArrayList;
import java.util.HashMap;

class Environment {
    final Environment enclosing;
    private final ArrayList<Object> values = new ArrayList<>();

    Environment() {
        enclosing = null;
    }

    Environment(Environment enclosing) {
        this.enclosing = enclosing;
    }

    void define(Object value) {
        values.add(value);
    }

    Environment ancestor(int distance) {
        Environment environment = this;
        for (int i = 0; i < distance; i++) {
            environment = environment.enclosing;
        }
        return environment;
    }

    Object getAt(int distance, Integer index) {
        return ancestor(distance).values.get(index);
    }

    void assignAt(int distance, Integer index, Object value) {
        ancestor(distance).values.set(index, value);
    }

    void assign(Integer index, Object value) {
        values.set(index, value);
    }

    Object get(int index) {
        return values.get(index);
    }
}