/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/
#ifndef CPLUSPLUS_BACKWARDSSCANNER_H
#define CPLUSPLUS_BACKWARDSSCANNER_H

#include "SimpleLexer.h"

#include <QtGui/QTextCursor>
#include <QtGui/QTextBlock>

namespace CPlusPlus {

class CPLUSPLUS_EXPORT BackwardsScanner
{
    enum { MAX_BLOCK_COUNT = 10 };

public:
    explicit BackwardsScanner(const QTextCursor &cursor,
                              int maxBlockCount = MAX_BLOCK_COUNT,
                              const QString &suffix = QString());

    int startToken() const;

    int startPosition() const;

    QString text() const;
    QString mid(int index) const;

    QString text(int index) const;
    QStringRef textRef(int index) const;
    // 1-based
    Token LA(int index) const;

    // n-la token is [startToken - n]
    Token operator[](int index) const; // ### deprecate

    QString indentationString(int index) const;

    int startOfLine(int index) const;
    int startOfMatchingBrace(int index) const;
    int startOfBlock(int index) const;

    int size() const;

    static int previousBlockState(const QTextBlock &block);

private:
    const Token &fetchToken(int tokenIndex);

private:
    QList<Token> _tokens;
    int _offset;
    int _blocksTokenized;
    QTextBlock _block;
    SimpleLexer _tokenize;
    QString _text;
    int _maxBlockCount;
    int _startToken;
};

} // end of namespace CPlusPlus

#endif // CPLUSPLUS_BACKWARDSSCANNER_H
