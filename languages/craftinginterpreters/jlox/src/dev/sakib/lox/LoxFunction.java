package dev.sakib.lox;

import java.util.List;

public class LoxFunction implements LoxCallable {
    private final List<Token> params;
    private final List<Stmt> body;
    private final Token name;
    private final Environment closure;

    public LoxFunction(Stmt.Function declaration, Environment closure) {
        this.params = declaration.params;
        this.body = declaration.body;
        this.name = declaration.name;
        this.closure = closure;
    }

    public LoxFunction(Expr.Function declaration, Environment closure) {
        this.params = declaration.params;
        this.body = declaration.body;
        this.name = null;
        this.closure = closure;
    }

    LoxFunction bind(LoxInstance instance) {
        Environment environment = new Environment(closure);
        environment.define(instance);
        return new LoxFunction(new Stmt.Function(this.name, this.params, this.body), environment);
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
            return returnValue.value;
        }

        return null;
    }
}
