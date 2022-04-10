package dev.sakib.lox;

import java.util.List;

public class LoxFunction implements LoxCallable {
    private final List<Token> params;
    private final List<Stmt> body;
    private final Token name;
    private final Environment closure;
    private final boolean isInitializer;

    public LoxFunction(Stmt.Function declaration, Environment closure, boolean isInitializer) {
        this.params = declaration.params;
        this.body = declaration.body;
        this.name = declaration.name;
        this.closure = closure;
        this.isInitializer = isInitializer;
    }

    public LoxFunction(Expr.Function declaration, Environment closure) {
        this.params = declaration.params;
        this.body = declaration.body;
        this.name = null;
        this.closure = closure;
        this.isInitializer = false;
    }

    LoxFunction bind(LoxInstance instance) {
        Environment environment = new Environment(closure);
        environment.define(instance);
        return new LoxFunction(new Stmt.Function(name, params, body), environment, isInitializer);
    }

    @Override
    public String toString() {
        return "<fn " + (name != null ? name.lexeme : "anonymous") + ">";
    }

    @Override
    public int arity() {
        return params.size();
    }

    @Override
    public Object call(Interpreter interpreter, List<Object> arguments) {
        Environment environment = new Environment(closure);
        for (int i = 0; i < params.size(); i++) {
            environment.define(arguments.get(i));
        }
        try {
            interpreter.executeBlock(body, environment);
        } catch (Return returnValue) {
            if (isInitializer) return closure.getAt(0, 0);
            return returnValue.value;
        }

        if (isInitializer) return closure.getAt(0, 0);

        return null;
    }
}
