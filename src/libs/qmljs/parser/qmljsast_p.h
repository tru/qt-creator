/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMLJSAST_P_H
#define QMLJSAST_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qmljsastvisitor_p.h"
#include "qmljsglobal_p.h"

#include <QtCore/QString>

QT_QML_BEGIN_NAMESPACE

#define QMLJS_DECLARE_AST_NODE(name) \
  enum { K = Kind_##name };

namespace QSOperator // ### rename
{

enum Op {
    Add,
    And,
    InplaceAnd,
    Assign,
    BitAnd,
    BitOr,
    BitXor,
    InplaceSub,
    Div,
    InplaceDiv,
    Equal,
    Ge,
    Gt,
    In,
    InplaceAdd,
    InstanceOf,
    Le,
    LShift,
    InplaceLeftShift,
    Lt,
    Mod,
    InplaceMod,
    Mul,
    InplaceMul,
    NotEqual,
    Or,
    InplaceOr,
    RShift,
    InplaceRightShift,
    StrictEqual,
    StrictNotEqual,
    Sub,
    URShift,
    InplaceURightShift,
    InplaceXor
};

} // namespace QSOperator

namespace QmlJS {
class NameId;
namespace AST {

template <typename _T1, typename _T2>
_T1 cast(_T2 *ast)
{
    if (ast && ast->kind == static_cast<_T1>(0)->K)
        return static_cast<_T1>(ast);

    return 0;
}

class QML_PARSER_EXPORT Node
{
public:
    enum Kind {
        Kind_Undefined,

        Kind_ArgumentList,
        Kind_ArrayLiteral,
        Kind_ArrayMemberExpression,
        Kind_BinaryExpression,
        Kind_Block,
        Kind_BreakStatement,
        Kind_CallExpression,
        Kind_CaseBlock,
        Kind_CaseClause,
        Kind_CaseClauses,
        Kind_Catch,
        Kind_ConditionalExpression,
        Kind_ContinueStatement,
        Kind_DebuggerStatement,
        Kind_DefaultClause,
        Kind_DeleteExpression,
        Kind_DoWhileStatement,
        Kind_ElementList,
        Kind_Elision,
        Kind_EmptyStatement,
        Kind_Expression,
        Kind_ExpressionStatement,
        Kind_FalseLiteral,
        Kind_FieldMemberExpression,
        Kind_Finally,
        Kind_ForEachStatement,
        Kind_ForStatement,
        Kind_FormalParameterList,
        Kind_FunctionBody,
        Kind_FunctionDeclaration,
        Kind_FunctionExpression,
        Kind_FunctionSourceElement,
        Kind_IdentifierExpression,
        Kind_IdentifierPropertyName,
        Kind_IfStatement,
        Kind_LabelledStatement,
        Kind_LocalForEachStatement,
        Kind_LocalForStatement,
        Kind_NewExpression,
        Kind_NewMemberExpression,
        Kind_NotExpression,
        Kind_NullExpression,
        Kind_NumericLiteral,
        Kind_NumericLiteralPropertyName,
        Kind_ObjectLiteral,
        Kind_PostDecrementExpression,
        Kind_PostIncrementExpression,
        Kind_PreDecrementExpression,
        Kind_PreIncrementExpression,
        Kind_Program,
        Kind_PropertyName,
        Kind_PropertyNameAndValueList,
        Kind_RegExpLiteral,
        Kind_ReturnStatement,
        Kind_SourceElement,
        Kind_SourceElements,
        Kind_StatementList,
        Kind_StatementSourceElement,
        Kind_StringLiteral,
        Kind_StringLiteralPropertyName,
        Kind_SwitchStatement,
        Kind_ThisExpression,
        Kind_ThrowStatement,
        Kind_TildeExpression,
        Kind_TrueLiteral,
        Kind_TryStatement,
        Kind_TypeOfExpression,
        Kind_UnaryMinusExpression,
        Kind_UnaryPlusExpression,
        Kind_VariableDeclaration,
        Kind_VariableDeclarationList,
        Kind_VariableStatement,
        Kind_VoidExpression,
        Kind_WhileStatement,
        Kind_WithStatement,
        Kind_NestedExpression,

        Kind_UiArrayBinding,
        Kind_UiImport,
        Kind_UiImportList,
        Kind_UiObjectBinding,
        Kind_UiObjectDefinition,
        Kind_UiObjectInitializer,
        Kind_UiObjectMemberList,
        Kind_UiArrayMemberList,
        Kind_UiProgram,
        Kind_UiParameterList,
        Kind_UiPublicMember,
        Kind_UiQualifiedId,
        Kind_UiScriptBinding,
        Kind_UiSourceElement,
        Kind_UiFormal,
        Kind_UiFormalList,
        Kind_UiSignature
    };

    inline Node()
        : kind(Kind_Undefined) {}

    virtual ~Node() {}

    virtual ExpressionNode *expressionCast();
    virtual BinaryExpression *binaryExpressionCast();
    virtual Statement *statementCast();
    virtual UiObjectMember *uiObjectMemberCast();

    void accept(Visitor *visitor);
    static void accept(Node *node, Visitor *visitor);

    inline static void acceptChild(Node *node, Visitor *visitor)
    { return accept(node, visitor); } // ### remove

    virtual void accept0(Visitor *visitor) = 0;

// attributes
    int kind;
};

class QML_PARSER_EXPORT ExpressionNode: public Node
{
public:
    ExpressionNode() {}
    virtual ~ExpressionNode() {}

    virtual ExpressionNode *expressionCast();

    virtual SourceLocation firstSourceLocation() const = 0;
    virtual SourceLocation lastSourceLocation() const = 0;
};

class QML_PARSER_EXPORT Statement: public Node
{
public:
    Statement() {}
    virtual ~Statement() {}

    virtual Statement *statementCast();

    virtual SourceLocation firstSourceLocation() const = 0;
    virtual SourceLocation lastSourceLocation() const = 0;
};

class QML_PARSER_EXPORT UiFormal: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiFormal)

    explicit UiFormal(NameId *name, NameId *alias = 0)
      : name(name), alias(alias)
    { }

    virtual SourceLocation firstSourceLocation() const
    { return SourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return SourceLocation(); }

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *name;
    NameId *alias;
    SourceLocation identifierToken;
    SourceLocation asToken;
    SourceLocation aliasToken;
};

class QML_PARSER_EXPORT UiFormalList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiFormalList)

    UiFormalList(UiFormal *formal)
            : formal(formal), next(this) {}

    UiFormalList(UiFormalList *previous, UiFormal *formal)
            : formal(formal)
    {
        next = previous->next;
        previous->next = this;
    }

    UiFormalList *finish()
    {
        UiFormalList *head = next;
        next = 0;
        return head;
    }

    virtual SourceLocation firstSourceLocation() const
    { return SourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return SourceLocation(); }

    virtual void accept0(Visitor *visitor);

// attributes
    UiFormal *formal;
    UiFormalList *next;
};

class QML_PARSER_EXPORT UiSignature: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiSignature)

    UiSignature(UiFormalList *formals = 0)
        : formals(formals)
    { }

    virtual SourceLocation firstSourceLocation() const
    { return SourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return SourceLocation(); }

    virtual void accept0(Visitor *visitor);

// attributes
    SourceLocation lparenToken;
    UiFormalList *formals;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT NestedExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NestedExpression)

    NestedExpression(ExpressionNode *expression)
        : expression(expression)
    { kind = K; }

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return lparenToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rparenToken; }

// attributes
    ExpressionNode *expression;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT ThisExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(ThisExpression)

    ThisExpression() { kind = K; }
    virtual ~ThisExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return thisToken; }

    virtual SourceLocation lastSourceLocation() const
    { return thisToken; }

// attributes
    SourceLocation thisToken;
};

class QML_PARSER_EXPORT IdentifierExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(IdentifierExpression)

    IdentifierExpression(NameId *n):
        name (n) { kind = K; }

    virtual ~IdentifierExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return identifierToken; }

    virtual SourceLocation lastSourceLocation() const
    { return identifierToken; }

// attributes
    NameId *name;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT NullExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NullExpression)

    NullExpression() { kind = K; }
    virtual ~NullExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return nullToken; }

    virtual SourceLocation lastSourceLocation() const
    { return nullToken; }

// attributes
    SourceLocation nullToken;
};

class QML_PARSER_EXPORT TrueLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(TrueLiteral)

    TrueLiteral() { kind = K; }
    virtual ~TrueLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return trueToken; }

    virtual SourceLocation lastSourceLocation() const
    { return trueToken; }

// attributes
    SourceLocation trueToken;
};

class QML_PARSER_EXPORT FalseLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(FalseLiteral)

    FalseLiteral() { kind = K; }
    virtual ~FalseLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return falseToken; }

    virtual SourceLocation lastSourceLocation() const
    { return falseToken; }

// attributes
    SourceLocation falseToken;
};

class QML_PARSER_EXPORT NumericLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NumericLiteral)

    NumericLiteral(double v):
        value(v) { kind = K; }
    virtual ~NumericLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return literalToken; }

    virtual SourceLocation lastSourceLocation() const
    { return literalToken; }

// attributes:
    double value;
    SourceLocation literalToken;
};

class QML_PARSER_EXPORT StringLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(StringLiteral)

    StringLiteral(NameId *v):
        value (v) { kind = K; }

    virtual ~StringLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return literalToken; }

    virtual SourceLocation lastSourceLocation() const
    { return literalToken; }

// attributes:
    NameId *value;
    SourceLocation literalToken;
};

class QML_PARSER_EXPORT RegExpLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(RegExpLiteral)

    RegExpLiteral(NameId *p, int f):
        pattern (p), flags (f) { kind = K; }

    virtual ~RegExpLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return literalToken; }

    virtual SourceLocation lastSourceLocation() const
    { return literalToken; }

// attributes:
    NameId *pattern;
    int flags;
    SourceLocation literalToken;
};

class QML_PARSER_EXPORT ArrayLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(ArrayLiteral)

    ArrayLiteral(Elision *e):
        elements (0), elision (e)
        { kind = K; }

    ArrayLiteral(ElementList *elts):
        elements (elts), elision (0)
        { kind = K; }

    ArrayLiteral(ElementList *elts, Elision *e):
        elements (elts), elision (e)
        { kind = K; }

    virtual ~ArrayLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return lbracketToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rbracketToken; }

// attributes
    ElementList *elements;
    Elision *elision;
    SourceLocation lbracketToken;
    SourceLocation commaToken;
    SourceLocation rbracketToken;
};

class QML_PARSER_EXPORT ObjectLiteral: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(ObjectLiteral)

    ObjectLiteral():
        properties (0) { kind = K; }

    ObjectLiteral(PropertyNameAndValueList *plist):
        properties (plist) { kind = K; }

    virtual ~ObjectLiteral() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return lbraceToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rbraceToken; }

// attributes
    PropertyNameAndValueList *properties;
    SourceLocation lbraceToken;
    SourceLocation rbraceToken;
};

class QML_PARSER_EXPORT ElementList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(ElementList)

    ElementList(Elision *e, ExpressionNode *expr):
        elision (e), expression (expr), next (this)
    { kind = K; }

    ElementList(ElementList *previous, Elision *e, ExpressionNode *expr):
        elision (e), expression (expr)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~ElementList() {}

    inline ElementList *finish ()
    {
        ElementList *front = next;
        next = 0;
        return front;
    }

    virtual void accept0(Visitor *visitor);

// attributes
    Elision *elision;
    ExpressionNode *expression;
    ElementList *next;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT Elision: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(Elision)

    Elision():
        next (this) { kind = K; }

    Elision(Elision *previous)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~Elision() {}

    virtual void accept0(Visitor *visitor);

    inline Elision *finish ()
    {
        Elision *front = next;
        next = 0;
        return front;
    }

// attributes
    Elision *next;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT PropertyNameAndValueList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(PropertyNameAndValueList)

    PropertyNameAndValueList(PropertyName *n, ExpressionNode *v):
        name (n), value (v), next (this)
        { kind = K; }

    PropertyNameAndValueList(PropertyNameAndValueList *previous, PropertyName *n, ExpressionNode *v):
        name (n), value (v)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~PropertyNameAndValueList() {}

    virtual void accept0(Visitor *visitor);

    inline PropertyNameAndValueList *finish ()
    {
        PropertyNameAndValueList *front = next;
        next = 0;
        return front;
    }

// attributes
    PropertyName *name;
    ExpressionNode *value;
    PropertyNameAndValueList *next;
    SourceLocation colonToken;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT PropertyName: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(PropertyName)

    PropertyName() { kind = K; }
    virtual ~PropertyName() {}

// attributes
    SourceLocation propertyNameToken;
};

class QML_PARSER_EXPORT IdentifierPropertyName: public PropertyName
{
public:
    QMLJS_DECLARE_AST_NODE(IdentifierPropertyName)

    IdentifierPropertyName(NameId *n):
        id (n) { kind = K; }

    virtual ~IdentifierPropertyName() {}

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *id;
};

class QML_PARSER_EXPORT StringLiteralPropertyName: public PropertyName
{
public:
    QMLJS_DECLARE_AST_NODE(StringLiteralPropertyName)

    StringLiteralPropertyName(NameId *n):
        id (n) { kind = K; }
    virtual ~StringLiteralPropertyName() {}

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *id;
};

class QML_PARSER_EXPORT NumericLiteralPropertyName: public PropertyName
{
public:
    QMLJS_DECLARE_AST_NODE(NumericLiteralPropertyName)

    NumericLiteralPropertyName(double n):
        id (n) { kind = K; }
    virtual ~NumericLiteralPropertyName() {}

    virtual void accept0(Visitor *visitor);

// attributes
    double id;
};

class QML_PARSER_EXPORT ArrayMemberExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(ArrayMemberExpression)

    ArrayMemberExpression(ExpressionNode *b, ExpressionNode *e):
        base (b), expression (e)
        { kind = K; }

    virtual ~ArrayMemberExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return base->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return rbracketToken; }

// attributes
    ExpressionNode *base;
    ExpressionNode *expression;
    SourceLocation lbracketToken;
    SourceLocation rbracketToken;
};

class QML_PARSER_EXPORT FieldMemberExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(FieldMemberExpression)

    FieldMemberExpression(ExpressionNode *b, NameId *n):
        base (b), name (n)
        { kind = K; }

    virtual ~FieldMemberExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return base->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return identifierToken; }

    // attributes
    ExpressionNode *base;
    NameId *name;
    SourceLocation dotToken;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT NewMemberExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NewMemberExpression)

    NewMemberExpression(ExpressionNode *b, ArgumentList *a):
        base (b), arguments (a)
        { kind = K; }

    virtual ~NewMemberExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return newToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rparenToken; }

    // attributes
    ExpressionNode *base;
    ArgumentList *arguments;
    SourceLocation newToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT NewExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NewExpression)

    NewExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~NewExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return newToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation newToken;
};

class QML_PARSER_EXPORT CallExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(CallExpression)

    CallExpression(ExpressionNode *b, ArgumentList *a):
        base (b), arguments (a)
        { kind = K; }

    virtual ~CallExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return base->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return rparenToken; }

// attributes
    ExpressionNode *base;
    ArgumentList *arguments;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT ArgumentList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(ArgumentList)

    ArgumentList(ExpressionNode *e):
        expression (e), next (this)
        { kind = K; }

    ArgumentList(ArgumentList *previous, ExpressionNode *e):
        expression (e)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~ArgumentList() {}

    virtual void accept0(Visitor *visitor);

    inline ArgumentList *finish ()
    {
        ArgumentList *front = next;
        next = 0;
        return front;
    }

// attributes
    ExpressionNode *expression;
    ArgumentList *next;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT PostIncrementExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(PostIncrementExpression)

    PostIncrementExpression(ExpressionNode *b):
        base (b) { kind = K; }

    virtual ~PostIncrementExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return base->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return incrementToken; }

// attributes
    ExpressionNode *base;
    SourceLocation incrementToken;
};

class QML_PARSER_EXPORT PostDecrementExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(PostDecrementExpression)

    PostDecrementExpression(ExpressionNode *b):
        base (b) { kind = K; }

    virtual ~PostDecrementExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return base->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return decrementToken; }

// attributes
    ExpressionNode *base;
    SourceLocation decrementToken;
};

class QML_PARSER_EXPORT DeleteExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(DeleteExpression)

    DeleteExpression(ExpressionNode *e):
        expression (e) { kind = K; }
    virtual ~DeleteExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return deleteToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation deleteToken;
};

class QML_PARSER_EXPORT VoidExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(VoidExpression)

    VoidExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~VoidExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return voidToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation voidToken;
};

class QML_PARSER_EXPORT TypeOfExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(TypeOfExpression)

    TypeOfExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~TypeOfExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return typeofToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation typeofToken;
};

class QML_PARSER_EXPORT PreIncrementExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(PreIncrementExpression)

    PreIncrementExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~PreIncrementExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return incrementToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation incrementToken;
};

class QML_PARSER_EXPORT PreDecrementExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(PreDecrementExpression)

    PreDecrementExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~PreDecrementExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return decrementToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation decrementToken;
};

class QML_PARSER_EXPORT UnaryPlusExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(UnaryPlusExpression)

    UnaryPlusExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~UnaryPlusExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return plusToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation plusToken;
};

class QML_PARSER_EXPORT UnaryMinusExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(UnaryMinusExpression)

    UnaryMinusExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~UnaryMinusExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return minusToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation minusToken;
};

class QML_PARSER_EXPORT TildeExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(TildeExpression)

    TildeExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~TildeExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return tildeToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation tildeToken;
};

class QML_PARSER_EXPORT NotExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(NotExpression)

    NotExpression(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~NotExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return notToken; }

    virtual SourceLocation lastSourceLocation() const
    { return expression->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    SourceLocation notToken;
};

class QML_PARSER_EXPORT BinaryExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(BinaryExpression)

    BinaryExpression(ExpressionNode *l, int o, ExpressionNode *r):
        left (l), op (o), right (r)
        { kind = K; }

    virtual ~BinaryExpression() {}

    virtual BinaryExpression *binaryExpressionCast();

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return left->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return right->lastSourceLocation(); }

// attributes
    ExpressionNode *left;
    int op;
    ExpressionNode *right;
    SourceLocation operatorToken;
};

class QML_PARSER_EXPORT ConditionalExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(ConditionalExpression)

    ConditionalExpression(ExpressionNode *e, ExpressionNode *t, ExpressionNode *f):
        expression (e), ok (t), ko (f)
        { kind = K; }

    virtual ~ConditionalExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return expression->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return ko->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    ExpressionNode *ok;
    ExpressionNode *ko;
    SourceLocation questionToken;
    SourceLocation colonToken;
};

class QML_PARSER_EXPORT Expression: public ExpressionNode // ### rename
{
public:
    QMLJS_DECLARE_AST_NODE(Expression)

    Expression(ExpressionNode *l, ExpressionNode *r):
        left (l), right (r) { kind = K; }

    virtual ~Expression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return left->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return right->lastSourceLocation(); }

// attributes
    ExpressionNode *left;
    ExpressionNode *right;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT Block: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(Block)

    Block(StatementList *slist):
        statements (slist) { kind = K; }

    virtual ~Block() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return lbraceToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rbraceToken; }

    // attributes
    StatementList *statements;
    SourceLocation lbraceToken;
    SourceLocation rbraceToken;
};

class QML_PARSER_EXPORT StatementList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(StatementList)

    StatementList(Statement *stmt):
        statement (stmt), next (this)
        { kind = K; }

    StatementList(StatementList *previous, Statement *stmt):
        statement (stmt)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~StatementList() {}

    virtual void accept0(Visitor *visitor);

    inline StatementList *finish ()
    {
        StatementList *front = next;
        next = 0;
        return front;
    }

// attributes
    Statement *statement;
    StatementList *next;
};

class QML_PARSER_EXPORT VariableStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(VariableStatement)

    VariableStatement(VariableDeclarationList *vlist):
        declarations (vlist)
        { kind = K; }

    virtual ~VariableStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return declarationKindToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    VariableDeclarationList *declarations;
    SourceLocation declarationKindToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT VariableDeclaration: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(VariableDeclaration)

    VariableDeclaration(NameId *n, ExpressionNode *e):
        name (n), expression (e), readOnly(false)
        { kind = K; }

    virtual ~VariableDeclaration() {}

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *name;
    ExpressionNode *expression;
    bool readOnly;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT VariableDeclarationList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(VariableDeclarationList)

    VariableDeclarationList(VariableDeclaration *decl):
        declaration (decl), next (this)
        { kind = K; }

    VariableDeclarationList(VariableDeclarationList *previous, VariableDeclaration *decl):
        declaration (decl)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~VariableDeclarationList() {}

    virtual void accept0(Visitor *visitor);

    inline VariableDeclarationList *finish (bool readOnly)
    {
        VariableDeclarationList *front = next;
        next = 0;
        if (readOnly) {
            VariableDeclarationList *vdl;
            for (vdl = front; vdl != 0; vdl = vdl->next)
                vdl->declaration->readOnly = true;
        }
        return front;
    }

// attributes
    VariableDeclaration *declaration;
    VariableDeclarationList *next;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT EmptyStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(EmptyStatement)

    EmptyStatement() { kind = K; }
    virtual ~EmptyStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return semicolonToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT ExpressionStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ExpressionStatement)

    ExpressionStatement(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~ExpressionStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return expression->firstSourceLocation(); }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    ExpressionNode *expression;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT IfStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(IfStatement)

    IfStatement(ExpressionNode *e, Statement *t, Statement *f = 0):
        expression (e), ok (t), ko (f)
        { kind = K; }

    virtual ~IfStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return ifToken; }

    virtual SourceLocation lastSourceLocation() const
    {
        if (ko)
            return ko->lastSourceLocation();

        return ok->lastSourceLocation();
    }

// attributes
    ExpressionNode *expression;
    Statement *ok;
    Statement *ko;
    SourceLocation ifToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
    SourceLocation elseToken;
};

class QML_PARSER_EXPORT DoWhileStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(DoWhileStatement)

    DoWhileStatement(Statement *stmt, ExpressionNode *e):
        statement (stmt), expression (e)
        { kind = K; }

    virtual ~DoWhileStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return doToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    Statement *statement;
    ExpressionNode *expression;
    SourceLocation doToken;
    SourceLocation whileToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT WhileStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(WhileStatement)

    WhileStatement(ExpressionNode *e, Statement *stmt):
        expression (e), statement (stmt)
        { kind = K; }

    virtual ~WhileStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return whileToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation whileToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT ForStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ForStatement)

    ForStatement(ExpressionNode *i, ExpressionNode *c, ExpressionNode *e, Statement *stmt):
        initialiser (i), condition (c), expression (e), statement (stmt)
        { kind = K; }

    virtual ~ForStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return forToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    ExpressionNode *initialiser;
    ExpressionNode *condition;
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation forToken;
    SourceLocation lparenToken;
    SourceLocation firstSemicolonToken;
    SourceLocation secondSemicolonToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT LocalForStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(LocalForStatement)

    LocalForStatement(VariableDeclarationList *vlist, ExpressionNode *c, ExpressionNode *e, Statement *stmt):
        declarations (vlist), condition (c), expression (e), statement (stmt)
        { kind = K; }

    virtual ~LocalForStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return forToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    VariableDeclarationList *declarations;
    ExpressionNode *condition;
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation forToken;
    SourceLocation lparenToken;
    SourceLocation varToken;
    SourceLocation firstSemicolonToken;
    SourceLocation secondSemicolonToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT ForEachStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ForEachStatement)

    ForEachStatement(ExpressionNode *i, ExpressionNode *e, Statement *stmt):
        initialiser (i), expression (e), statement (stmt)
        { kind = K; }

    virtual ~ForEachStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return forToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    ExpressionNode *initialiser;
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation forToken;
    SourceLocation lparenToken;
    SourceLocation inToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT LocalForEachStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(LocalForEachStatement)

    LocalForEachStatement(VariableDeclaration *v, ExpressionNode *e, Statement *stmt):
        declaration (v), expression (e), statement (stmt)
        { kind = K; }

    virtual ~LocalForEachStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return forToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    VariableDeclaration *declaration;
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation forToken;
    SourceLocation lparenToken;
    SourceLocation varToken;
    SourceLocation inToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT ContinueStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ContinueStatement)

    ContinueStatement(NameId *l = 0):
        label (l) { kind = K; }

    virtual ~ContinueStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return continueToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    NameId *label;
    SourceLocation continueToken;
    SourceLocation identifierToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT BreakStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(BreakStatement)

    BreakStatement(NameId *l = 0):
        label (l) { kind = K; }

    virtual ~BreakStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return breakToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

    // attributes
    NameId *label;
    SourceLocation breakToken;
    SourceLocation identifierToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT ReturnStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ReturnStatement)

    ReturnStatement(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~ReturnStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return returnToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    ExpressionNode *expression;
    SourceLocation returnToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT WithStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(WithStatement)

    WithStatement(ExpressionNode *e, Statement *stmt):
        expression (e), statement (stmt)
        { kind = K; }

    virtual ~WithStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return withToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    ExpressionNode *expression;
    Statement *statement;
    SourceLocation withToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT CaseBlock: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(CaseBlock)

    explicit CaseBlock(CaseClauses *c, DefaultClause *d = 0, CaseClauses *r = 0):
        clauses (c), defaultClause (d), moreClauses (r)
        { kind = K; }

    virtual ~CaseBlock() {}

    virtual void accept0(Visitor *visitor);

// attributes
    CaseClauses *clauses;
    DefaultClause *defaultClause;
    CaseClauses *moreClauses;
    SourceLocation lbraceToken;
    SourceLocation rbraceToken;
};

class QML_PARSER_EXPORT SwitchStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(SwitchStatement)

    SwitchStatement(ExpressionNode *e, CaseBlock *b):
        expression (e), block (b)
        { kind = K; }

    virtual ~SwitchStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return switchToken; }

    virtual SourceLocation lastSourceLocation() const
    { return block->rbraceToken; }

// attributes
    ExpressionNode *expression;
    CaseBlock *block;
    SourceLocation switchToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT CaseClauses: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(CaseClauses)

    CaseClauses(CaseClause *c):
        clause (c), next (this)
        { kind = K; }

    CaseClauses(CaseClauses *previous, CaseClause *c):
        clause (c)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~CaseClauses() {}

    virtual void accept0(Visitor *visitor);

    inline CaseClauses *finish ()
    {
        CaseClauses *front = next;
        next = 0;
        return front;
    }

//attributes
    CaseClause *clause;
    CaseClauses *next;
};

class QML_PARSER_EXPORT CaseClause: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(CaseClause)

    CaseClause(ExpressionNode *e, StatementList *slist):
        expression (e), statements (slist)
        { kind = K; }

    virtual ~CaseClause() {}

    virtual void accept0(Visitor *visitor);

// attributes
    ExpressionNode *expression;
    StatementList *statements;
    SourceLocation caseToken;
    SourceLocation colonToken;
};

class QML_PARSER_EXPORT DefaultClause: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(DefaultClause)

    DefaultClause(StatementList *slist):
        statements (slist)
        { kind = K; }

    virtual ~DefaultClause() {}

    virtual void accept0(Visitor *visitor);

// attributes
    StatementList *statements;
    SourceLocation defaultToken;
    SourceLocation colonToken;
};

class QML_PARSER_EXPORT LabelledStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(LabelledStatement)

    LabelledStatement(NameId *l, Statement *stmt):
        label (l), statement (stmt)
        { kind = K; }

    virtual ~LabelledStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return identifierToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

// attributes
    NameId *label;
    Statement *statement;
    SourceLocation identifierToken;
    SourceLocation colonToken;
};

class QML_PARSER_EXPORT ThrowStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(ThrowStatement)

    ThrowStatement(ExpressionNode *e):
        expression (e) { kind = K; }

    virtual ~ThrowStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return throwToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

    // attributes
    ExpressionNode *expression;
    SourceLocation throwToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT Catch: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(Catch)

    Catch(NameId *n, Block *stmt):
        name (n), statement (stmt)
        { kind = K; }

    virtual ~Catch() {}

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *name;
    Block *statement;
    SourceLocation catchToken;
    SourceLocation lparenToken;
    SourceLocation identifierToken;
    SourceLocation rparenToken;
};

class QML_PARSER_EXPORT Finally: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(Finally)

    Finally(Block *stmt):
        statement (stmt)
        { kind = K; }

    virtual ~Finally() {}

    virtual void accept0(Visitor *visitor);

// attributes
    Block *statement;
    SourceLocation finallyToken;
};

class QML_PARSER_EXPORT TryStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(TryStatement)

    TryStatement(Statement *stmt, Catch *c, Finally *f):
        statement (stmt), catchExpression (c), finallyExpression (f)
        { kind = K; }

    TryStatement(Statement *stmt, Finally *f):
        statement (stmt), catchExpression (0), finallyExpression (f)
        { kind = K; }

    TryStatement(Statement *stmt, Catch *c):
        statement (stmt), catchExpression (c), finallyExpression (0)
        { kind = K; }

    virtual ~TryStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return tryToken; }

    virtual SourceLocation lastSourceLocation() const
    {
        if (finallyExpression)
            return finallyExpression->statement->rbraceToken;
        else if (catchExpression)
            return catchExpression->statement->rbraceToken;

        return statement->lastSourceLocation();
    }

// attributes
    Statement *statement;
    Catch *catchExpression;
    Finally *finallyExpression;
    SourceLocation tryToken;
};

class QML_PARSER_EXPORT FunctionExpression: public ExpressionNode
{
public:
    QMLJS_DECLARE_AST_NODE(FunctionExpression)

    FunctionExpression(NameId *n, FormalParameterList *f, FunctionBody *b):
        name (n), formals (f), body (b)
        { kind = K; }

    virtual ~FunctionExpression() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return functionToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rbraceToken; }

// attributes
    NameId *name;
    FormalParameterList *formals;
    FunctionBody *body;
    SourceLocation functionToken;
    SourceLocation identifierToken;
    SourceLocation lparenToken;
    SourceLocation rparenToken;
    SourceLocation lbraceToken;
    SourceLocation rbraceToken;
};

class QML_PARSER_EXPORT FunctionDeclaration: public FunctionExpression
{
public:
    QMLJS_DECLARE_AST_NODE(FunctionDeclaration)

    FunctionDeclaration(NameId *n, FormalParameterList *f, FunctionBody *b):
        FunctionExpression(n, f, b)
        { kind = K; }

    virtual ~FunctionDeclaration() {}

    virtual void accept0(Visitor *visitor);
};

class QML_PARSER_EXPORT FormalParameterList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(FormalParameterList)

    FormalParameterList(NameId *n):
        name (n), next (this)
        { kind = K; }

    FormalParameterList(FormalParameterList *previous, NameId *n):
        name (n)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~FormalParameterList() {}

    virtual void accept0(Visitor *visitor);

    inline FormalParameterList *finish ()
    {
        FormalParameterList *front = next;
        next = 0;
        return front;
    }

// attributes
    NameId *name;
    FormalParameterList *next;
    SourceLocation commaToken;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT FunctionBody: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(FunctionBody)

    FunctionBody(SourceElements *elts):
        elements (elts)
        { kind = K; }

    virtual ~FunctionBody() {}

    virtual void accept0(Visitor *visitor);

// attributes
    SourceElements *elements;
};

class QML_PARSER_EXPORT Program: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(Program)

    Program(SourceElements *elts):
        elements (elts)
        { kind = K; }

    virtual ~Program() {}

    virtual void accept0(Visitor *visitor);

// attributes
    SourceElements *elements;
};

class QML_PARSER_EXPORT SourceElements: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(SourceElements)

    SourceElements(SourceElement *elt):
        element (elt), next (this)
        { kind = K; }

    SourceElements(SourceElements *previous, SourceElement *elt):
        element (elt)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~SourceElements() {}

    virtual void accept0(Visitor *visitor);

    inline SourceElements *finish ()
    {
        SourceElements *front = next;
        next = 0;
        return front;
    }

// attributes
    SourceElement *element;
    SourceElements *next;
};

class QML_PARSER_EXPORT SourceElement: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(SourceElement)

    inline SourceElement()
        { kind = K; }

    virtual ~SourceElement() {}
};

class QML_PARSER_EXPORT FunctionSourceElement: public SourceElement
{
public:
    QMLJS_DECLARE_AST_NODE(FunctionSourceElement)

    FunctionSourceElement(FunctionDeclaration *f):
        declaration (f)
        { kind = K; }

    virtual ~FunctionSourceElement() {}

    virtual void accept0(Visitor *visitor);

// attributes
    FunctionDeclaration *declaration;
};

class QML_PARSER_EXPORT StatementSourceElement: public SourceElement
{
public:
    QMLJS_DECLARE_AST_NODE(StatementSourceElement)

    StatementSourceElement(Statement *stmt):
        statement (stmt)
        { kind = K; }

    virtual ~StatementSourceElement() {}

    virtual void accept0(Visitor *visitor);

// attributes
    Statement *statement;
};

class QML_PARSER_EXPORT DebuggerStatement: public Statement
{
public:
    QMLJS_DECLARE_AST_NODE(DebuggerStatement)

    DebuggerStatement()
        { kind = K; }

    virtual ~DebuggerStatement() {}

    virtual void accept0(Visitor *visitor);

    virtual SourceLocation firstSourceLocation() const
    { return debuggerToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

// attributes
    SourceLocation debuggerToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT UiProgram: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiProgram)

    UiProgram(UiImportList *imports, UiObjectMemberList *members)
        : imports(imports), members(members)
    { kind = K; }

    virtual void accept0(Visitor *visitor);

// attributes
    UiImportList *imports;
    UiObjectMemberList *members;
};

class QML_PARSER_EXPORT UiQualifiedId: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiQualifiedId)

    UiQualifiedId(NameId *name)
        : next(this), name(name)
    { kind = K; }

    UiQualifiedId(UiQualifiedId *previous, NameId *name)
        : name(name)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~UiQualifiedId() {}

    UiQualifiedId *finish()
    {
        UiQualifiedId *head = next;
        next = 0;
        return head;
    }

    virtual void accept0(Visitor *visitor);

// attributes
    UiQualifiedId *next;
    NameId *name;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT UiImport: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiImport)

    UiImport(NameId *fileName)
        : fileName(fileName), importUri(0), importId(0)
    { kind = K; }

    UiImport(UiQualifiedId *uri)
        : fileName(0), importUri(uri), importId(0)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    { return importToken; }

    virtual SourceLocation lastSourceLocation() const
    { return semicolonToken; }

    virtual void accept0(Visitor *visitor);

// attributes
    NameId *fileName;
    UiQualifiedId *importUri;
    NameId *importId;
    SourceLocation importToken;
    SourceLocation fileNameToken;
    SourceLocation versionToken;
    SourceLocation asToken;
    SourceLocation importIdToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT UiImportList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiImportList)

    UiImportList(UiImport *import)
        : import(import),
          next(this)
    { kind = K; }

    UiImportList(UiImportList *previous, UiImport *import)
        : import(import)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual SourceLocation firstSourceLocation() const
    {
        if (import) return import->firstSourceLocation();
        else return SourceLocation();
    }

    virtual SourceLocation lastSourceLocation() const
    {
        for (const UiImportList *it = this; it; it = it->next)
            if (!it->next && it->import)
                return it->import->lastSourceLocation();

        return SourceLocation();
    }

    UiImportList *finish()
    {
        UiImportList *head = next;
        next = 0;
        return head;
    }

    virtual void accept0(Visitor *visitor);

// attributes
    UiImport *import;
    UiImportList *next;
};

class QML_PARSER_EXPORT UiObjectMember: public Node
{
public:
    virtual SourceLocation firstSourceLocation() const = 0;
    virtual SourceLocation lastSourceLocation() const = 0;

    virtual UiObjectMember *uiObjectMemberCast();
};

class QML_PARSER_EXPORT UiObjectMemberList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiObjectMemberList)

    UiObjectMemberList(UiObjectMember *member)
        : next(this), member(member)
    { kind = K; }

    UiObjectMemberList(UiObjectMemberList *previous, UiObjectMember *member)
        : member(member)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual void accept0(Visitor *visitor);

    UiObjectMemberList *finish()
    {
        UiObjectMemberList *head = next;
        next = 0;
        return head;
    }

// attributes
    UiObjectMemberList *next;
    UiObjectMember *member;
};

class QML_PARSER_EXPORT UiArrayMemberList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiArrayMemberList)

    UiArrayMemberList(UiObjectMember *member)
        : next(this), member(member)
    { kind = K; }

    UiArrayMemberList(UiArrayMemberList *previous, UiObjectMember *member)
        : member(member)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual void accept0(Visitor *visitor);

    UiArrayMemberList *finish()
    {
        UiArrayMemberList *head = next;
        next = 0;
        return head;
    }

// attributes
    UiArrayMemberList *next;
    UiObjectMember *member;
    SourceLocation commaToken;
};

class QML_PARSER_EXPORT UiObjectInitializer: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiObjectInitializer)

    UiObjectInitializer(UiObjectMemberList *members)
        : members(members)
    { kind = K; }

    virtual void accept0(Visitor *visitor);

// attributes
    SourceLocation lbraceToken;
    UiObjectMemberList *members;
    SourceLocation rbraceToken;
};

class QML_PARSER_EXPORT UiParameterList: public Node
{
public:
    QMLJS_DECLARE_AST_NODE(UiParameterList)

    UiParameterList(NameId *t, NameId *n):
        type (t), name (n), next (this)
        { kind = K; }

    UiParameterList(UiParameterList *previous, NameId *t, NameId *n):
        type (t), name (n)
    {
        kind = K;
        next = previous->next;
        previous->next = this;
    }

    virtual ~UiParameterList() {}

    virtual void accept0(Visitor *) {}

    inline UiParameterList *finish ()
    {
        UiParameterList *front = next;
        next = 0;
        return front;
    }

// attributes
    NameId *type;
    NameId *name;
    UiParameterList *next;
    SourceLocation commaToken;
    SourceLocation identifierToken;
};

class QML_PARSER_EXPORT UiPublicMember: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiPublicMember)

    UiPublicMember(NameId *memberType,
                   NameId *name)
        : type(Property), typeModifier(0), memberType(memberType), name(name), expression(0), binding(0), isDefaultMember(false), isReadonlyMember(false), parameters(0)
    { kind = K; }

    UiPublicMember(NameId *memberType,
                   NameId *name,
                   ExpressionNode *expression)
        : type(Property), typeModifier(0), memberType(memberType), name(name), expression(expression), binding(0), isDefaultMember(false), isReadonlyMember(false), parameters(0)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    {
      if (defaultToken.isValid())
        return defaultToken;
      else if (readonlyToken.isValid())
          return readonlyToken;

      return propertyToken;
    }

    virtual SourceLocation lastSourceLocation() const
    {
      if (binding)
          return binding->lastSourceLocation();

      return semicolonToken;
    }

    virtual void accept0(Visitor *visitor);

// attributes
    enum { Signal, Property } type;
    NameId *typeModifier;
    NameId *memberType;
    NameId *name;
    ExpressionNode *expression; // initialized with a JS expression
    UiObjectMember *binding; // initialized with a QML object or array.
    bool isDefaultMember;
    bool isReadonlyMember;
    UiParameterList *parameters;
    SourceLocation defaultToken;
    SourceLocation readonlyToken;
    SourceLocation propertyToken;
    SourceLocation typeModifierToken;
    SourceLocation typeToken;
    SourceLocation identifierToken;
    SourceLocation colonToken;
    SourceLocation semicolonToken;
};

class QML_PARSER_EXPORT UiObjectDefinition: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiObjectDefinition)

    UiObjectDefinition(UiQualifiedId *qualifiedTypeNameId,
                       UiObjectInitializer *initializer)
        : qualifiedTypeNameId(qualifiedTypeNameId), initializer(initializer)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    { return qualifiedTypeNameId->identifierToken; }

    virtual SourceLocation lastSourceLocation() const
    { return initializer->rbraceToken; }

    virtual void accept0(Visitor *visitor);

// attributes
    UiQualifiedId *qualifiedTypeNameId;
    UiObjectInitializer *initializer;
};

class QML_PARSER_EXPORT UiSourceElement: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiSourceElement)

    UiSourceElement(Node *sourceElement)
        : sourceElement(sourceElement)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    {
      if (FunctionDeclaration *funDecl = cast<FunctionDeclaration *>(sourceElement))
        return funDecl->firstSourceLocation();
      else if (VariableStatement *varStmt = cast<VariableStatement *>(sourceElement))
        return varStmt->firstSourceLocation();

      return SourceLocation();
    }

    virtual SourceLocation lastSourceLocation() const
    {
      if (FunctionDeclaration *funDecl = cast<FunctionDeclaration *>(sourceElement))
        return funDecl->lastSourceLocation();
      else if (VariableStatement *varStmt = cast<VariableStatement *>(sourceElement))
        return varStmt->lastSourceLocation();

      return SourceLocation();
    }


    virtual void accept0(Visitor *visitor);

// attributes
    Node *sourceElement;
};

class QML_PARSER_EXPORT UiObjectBinding: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiObjectBinding)

    UiObjectBinding(UiQualifiedId *qualifiedId,
                    UiQualifiedId *qualifiedTypeNameId,
                    UiObjectInitializer *initializer)
        : qualifiedId(qualifiedId),
          qualifiedTypeNameId(qualifiedTypeNameId),
          initializer(initializer),
          hasOnToken(false)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    {
        if (hasOnToken && qualifiedTypeNameId)
            return qualifiedTypeNameId->identifierToken;

        return qualifiedId->identifierToken;
    }

    virtual SourceLocation lastSourceLocation() const
    { return initializer->rbraceToken; }

    virtual void accept0(Visitor *visitor);

// attributes
    UiQualifiedId *qualifiedId;
    UiQualifiedId *qualifiedTypeNameId;
    UiObjectInitializer *initializer;
    SourceLocation colonToken;
    bool hasOnToken;
};

class QML_PARSER_EXPORT UiScriptBinding: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiScriptBinding)

    UiScriptBinding(UiQualifiedId *qualifiedId,
                    Statement *statement)
        : qualifiedId(qualifiedId),
          statement(statement)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    { return qualifiedId->identifierToken; }

    virtual SourceLocation lastSourceLocation() const
    { return statement->lastSourceLocation(); }

    virtual void accept0(Visitor *visitor);

// attributes
    UiQualifiedId *qualifiedId;
    Statement *statement;
    SourceLocation colonToken;
};

class QML_PARSER_EXPORT UiArrayBinding: public UiObjectMember
{
public:
    QMLJS_DECLARE_AST_NODE(UiArrayBinding)

    UiArrayBinding(UiQualifiedId *qualifiedId,
                   UiArrayMemberList *members)
        : qualifiedId(qualifiedId),
          members(members)
    { kind = K; }

    virtual SourceLocation firstSourceLocation() const
    { return qualifiedId->identifierToken; }

    virtual SourceLocation lastSourceLocation() const
    { return rbracketToken; }

    virtual void accept0(Visitor *visitor);

// attributes
    UiQualifiedId *qualifiedId;
    UiArrayMemberList *members;
    SourceLocation colonToken;
    SourceLocation lbracketToken;
    SourceLocation rbracketToken;
};

} } // namespace AST



QT_QML_END_NAMESPACE

#endif
