package dev.sakib.lox;

import static dev.sakib.lox.TokenType.AND;
import static dev.sakib.lox.TokenType.BANG;
import static dev.sakib.lox.TokenType.BANG_EQUAL;
import static dev.sakib.lox.TokenType.BREAK;
import static dev.sakib.lox.TokenType.COLON;
import static dev.sakib.lox.TokenType.COMMA;
import static dev.sakib.lox.TokenType.CONTINUE;
import static dev.sakib.lox.TokenType.ELSE;
import static dev.sakib.lox.TokenType.EOF;
import static dev.sakib.lox.TokenType.EQUAL;
import static dev.sakib.lox.TokenType.EQUAL_EQUAL;
import static dev.sakib.lox.TokenType.FALSE;
import static dev.sakib.lox.TokenType.FOR;
import static dev.sakib.lox.TokenType.FUN;
import static dev.sakib.lox.TokenType.GREATER;
import static dev.sakib.lox.TokenType.GREATER_EQUAL;
import static dev.sakib.lox.TokenType.IDENTIFIER;
import static dev.sakib.lox.TokenType.IF;
import static dev.sakib.lox.TokenType.LEFT_BRACE;
import static dev.sakib.lox.TokenType.LEFT_PAREN;
import static dev.sakib.lox.TokenType.LESS;
import static dev.sakib.lox.TokenType.LESS_EQUAL;
import static dev.sakib.lox.TokenType.MINUS;
import static dev.sakib.lox.TokenType.NIL;
import static dev.sakib.lox.TokenType.NUMBER;
import static dev.sakib.lox.TokenType.OR;
import static dev.sakib.lox.TokenType.PLUS;
import static dev.sakib.lox.TokenType.PRINT;
import static dev.sakib.lox.TokenType.QUESTION;
import static dev.sakib.lox.TokenType.RETURN;
import static dev.sakib.lox.TokenType.RIGHT_BRACE;
import static dev.sakib.lox.TokenType.RIGHT_PAREN;
import static dev.sakib.lox.TokenType.SEMICOLON;
import static dev.sakib.lox.TokenType.SLASH;
import static dev.sakib.lox.TokenType.STAR;
import static dev.sakib.lox.TokenType.STRING;
import static dev.sakib.lox.TokenType.TRUE;
import static dev.sakib.lox.TokenType.VAR;
import static dev.sakib.lox.TokenType.WHILE;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Parser {
    private static class ParseError extends RuntimeException {
    }

    private final List<Token> tokens;
    private int current = 0;
    private boolean insideLoop = false;

    Parser(List<Token> tokens) {
        this.tokens = tokens;
    }

    List<Stmt> parse() {
        List<Stmt> statements = new ArrayList<>();
        while (!isAtEnd()) {
            statements.add(declaration());
        }

        return statements;
    }

    private Expr expression(boolean allowComma) {
        return allowComma?  comma() : assignment();
    }

    private Stmt declaration() {
        try {
            if (match(FUN)) return function("function");
            if (match(VAR)) return varDeclaration();

            return statement();
        } catch (ParseError error) {
            synchronize();
            return null;
        }
    }

    private Stmt statement() {
        if (match(CONTINUE)) return continueStatement();
        if (match(BREAK)) return breakStatement();
        if (match(FOR)) return forStatement();
        if (match(IF)) return ifStatement();
        if (match(PRINT)) return printStatement();
        if (match(RETURN)) return returnStatement();
        if (match(WHILE)) return whileStatement();
        if (match(LEFT_BRACE)) return new Stmt.Block(block());

        return expressionStatement();
    }

    private Stmt returnStatement() {
        Token keyword = previous();

        Expr value = null;
        if (!check(SEMICOLON)) {
            value = expression(true);
        }
        consume(SEMICOLON, "Expect ';' after return value");

        return new Stmt.Return(keyword, value);
    }

    private Stmt continueStatement() {
        if (!insideLoop) {
            throw  error(previous(), "continue not allowed outside loops");
        }
        consume(SEMICOLON, "Expect ';' after continue.");
        return new Stmt.Continue();
    }

    private Stmt breakStatement() {
        if (!insideLoop) {
            throw  error(previous(), "break not allowed outside loops");
        }
        consume(SEMICOLON, "Expect ';' after break.");
        return new Stmt.Break();
    }

    private Stmt forStatement() {
        consume(LEFT_PAREN, "Expect '(' after for.");

        Stmt initializer;
        if (match(SEMICOLON)) {
            initializer = null;
        } else if (match(VAR)) {
            initializer = varDeclaration();
        } else {
            initializer = expressionStatement();
        }

        Expr condition = null;
        if (!check(SEMICOLON)) {
            condition = expression(true);
        }
        consume(SEMICOLON, "Expect ';' after loop condition");

        Expr increment = null;
        if (!check(RIGHT_PAREN)) {
            increment = expression(true);
        }
        consume(RIGHT_PAREN, "Expect ')' after for clauses.");

        insideLoop = true;
        Stmt body = statement();
        insideLoop = false;

        if (increment != null) {
            body = new Stmt.Block(Arrays.asList(body, new Stmt.Expression(increment)));
        }

        if (condition == null) condition = new Expr.Literal(true);
        body = new Stmt.While(condition, body, true);

        if (increment != null) {
            body = new Stmt.Block(Arrays.asList(initializer, body));
        }

        return body;
    }

    private Stmt ifStatement() {
        consume(LEFT_PAREN, "Expect '(' after if.");
        Expr condition = expression(true);
        consume(RIGHT_PAREN, "Expect ')' after if condition");

        Stmt thenBranch = statement();
        Stmt elseBranch = null;
        if (match(ELSE)) {
            elseBranch = statement();
        }

        return new Stmt.If(condition, thenBranch, elseBranch);
    }

    private Stmt printStatement() {
        Expr value = expression(true);
        consume(SEMICOLON, "Expect ';' after value.");
        return new Stmt.Print(value);
    }

    private Stmt varDeclaration() {
        Token name = consume(IDENTIFIER, "Expect variable name.");

        Expr initializer = null;
        if (match(EQUAL)) {
            initializer = expression(true);
        }

        consume(SEMICOLON, "Expect ';' after variable declaration.");

        return new Stmt.Var(name, initializer);
    }

    private Stmt whileStatement() {
        consume(LEFT_PAREN, "Expect '(' after 'while'");
        Expr condition = expression(true);
        consume(RIGHT_PAREN, "Expect ')' after condition");
        insideLoop = true;
        Stmt body = statement();
        insideLoop = false;

        return new Stmt.While(condition, body, false);

    }

    private Stmt expressionStatement() {
        Expr value = expression(true);
        consume(SEMICOLON, "Expect ';' after expression.");
        return new Stmt.Expression(value);
    }

    private Stmt.Function function(String kind) {
        Token name = consume(IDENTIFIER, "Expect " + kind + " name.");
        consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
        List<Token> parameters = new ArrayList<>();

        if (!check(RIGHT_PAREN)) {
            do {
                if (parameters.size() >= 255) {
                    error(peek(), "Can't have more than 255 parameters");
                }

                parameters.add(consume(IDENTIFIER, "Expect parameter name."));
            } while (match(COMMA));
        }
        consume(RIGHT_PAREN, "Expect ')' after parameters");

        consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
        List<Stmt> body = block();
        return new Stmt.Function(name, parameters, body);
    }

    private List<Stmt> block() {
        List<Stmt> statements = new ArrayList<>();

        while (!check(RIGHT_BRACE) && !isAtEnd()) {
            statements.add(declaration());
        }

        consume(RIGHT_BRACE, "Expected '}' after block.");
        return statements;
    }

    private Expr assignment() {
        Expr expr = ternary();

        if (match(EQUAL)) {
            Token equals = previous();
            Expr value = assignment();

            if (expr instanceof Expr.Variable) {
                Token name = ((Expr.Variable) expr).name;
                return new Expr.Assign(name, value);
            }

            error(equals, "Invalid assignment target.");
        }

        return expr;
    }

    private Expr or() {
        Expr expr = and();

        while (match(OR)) {
            Token operator = previous();
            Expr right = and();
            expr = new  Expr.Logical(expr, operator, right);

        }

        return expr;
    }

    private Expr and() {
        Expr expr = equality();

        while (match(AND)) {
            Token operator = previous();
            Expr right = equality();
            expr = new Expr.Logical(expr, operator, right);
        }

        return  expr;
    }

    private Expr comma() {
        Expr expr = assignment();

        while (match(COMMA)) {
            Token operator = previous();
            Expr right = assignment();
            expr = new Expr.Binary(expr, operator, right);
        }

        return expr;
    }

    private Expr ternary() {
        Expr condition = or();

        if (match(QUESTION)) {
            Expr left = ternary();
            if (!match(COLON)) {
                throw error(peek(), "Expect ':' after expression");
            }
            Expr right = ternary();
            return new Expr.Ternary(condition, left, right);
        }
        return condition;
    }

    private Expr equality() {
        Expr expr = comparison();

        while (match(BANG_EQUAL, EQUAL_EQUAL)) {
            Token operator = previous();
            Expr right = comparison();
            expr = new Expr.Binary(expr, operator, right);
        }

        return expr;
    }

    private Expr comparison() {
        Expr expr = term();

        while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
            Token operator = previous();
            Expr right = term();
            expr = new Expr.Binary(expr, operator, right);
        }

        return expr;
    }

    private Expr term() {
        Expr expr = factor();

        while (match(MINUS, PLUS)) {
            Token operator = previous();
            Expr right = factor();
            expr = new Expr.Binary(expr, operator, right);
        }

        return expr;
    }

    private Expr factor() {
        Expr expr = unary();

        while (match(SLASH, STAR)) {
            Token operator = previous();
            Expr right = unary();
            expr = new Expr.Binary(expr, operator, right);
        }

        return expr;
    }

    private Expr unary() {
        if (match(BANG, MINUS)) {
            Token operator = previous();
            Expr right = unary();
            return new Expr.Unary(operator, right);
        }
        return call();
    }

    private Expr call() {
        Expr expr = primary();

        while (true) {
            if (match(LEFT_PAREN)) {
                expr = finishCall(expr);
            } else {
                break;
            }
        }

        return expr;
    }

    private Expr primary() {
        if (match(FALSE)) return new Expr.Literal(false);
        if (match(TRUE)) return new Expr.Literal(true);
        if (match(NIL)) return new Expr.Literal(null);

        if (match(NUMBER, STRING)) {
            return new Expr.Literal(previous().literal);
        }

        if (match(IDENTIFIER)) {
            return new Expr.Variable(previous());
        }

        if (match(LEFT_PAREN)) {
            Expr expr = expression(true);
            consume(RIGHT_PAREN, "Expect ')' after expression");
            return new Expr.Grouping(expr);
        }

        if (match(PLUS, MINUS, STAR, SLASH)) {
            error(previous(), "Binary operator without a left hand operand");
            term();
        } else {
            error(peek(), "Expect expression.");
        }
        return null;
    }

    private Expr finishCall(Expr callee) {
        List<Expr> arguments = new ArrayList<>();
        if (!check(RIGHT_PAREN)) {
            do {
                if (arguments.size() >= 255) {
                    error(peek(), "Can't have more than 255 arguments");
                }
                arguments.add(expression(false));
            } while (match(COMMA));
        }

        Token paren = consume(RIGHT_PAREN, "Expect ')' after arguments");

        return new Expr.Call(callee, paren, arguments);
    }

    private boolean match(TokenType... types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }

        return false;
    }

    private Token consume(TokenType type, String message) {
        if (check(type)) return advance();

        throw error(peek(), message);
    }

    private boolean check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    private Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    private boolean isAtEnd() {
        return peek().type == EOF;
    }

    private Token peek() {
        return tokens.get(current);
    }

    private Token previous() {
        return tokens.get(current - 1);
    }

    private ParseError error(Token token, String message) {
        Lox.error(token, message);
        return new ParseError();
    }

    private void synchronize() {
        advance();

        while (!isAtEnd()) {
            if (previous().type == SEMICOLON) return;

            switch (peek().type) {
                case CLASS:
                case FUN:
                case VAR:
                case FOR:
                case IF:
                case WHILE:
                case PRINT:
                case RETURN:
                    return;
            }

            advance();
        }
    }
}
