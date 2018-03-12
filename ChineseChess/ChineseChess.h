#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChineseChess.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>


#include <QLabel> 

class ChessPieces
{
private:
	bool whoseTurn;	//该哪边走
	int chesspieces[9][10] = { 0 };//棋子布局
	QPoint masterPos[2];				//存储将帅位置，为(-1,-1)时代表将帅被吃掉了。0存储我方，1存储对方
public:
	ChessPieces();
	int getPiece(int xpos, int ypos);//获取位置上的棋子
	bool getWhoseTurn();			//获取该哪边走棋
	bool doStep(QPoint start, QPoint end);	//执行一步走棋
	bool isPosInBoard(int x, int y);	//判断位置是否在棋盘上
};


class ChineseChess : public QMainWindow
{
	Q_OBJECT

protected:
	void mousePressEvent(QMouseEvent *event);
public:
	ChineseChess(QWidget *parent = Q_NULLPTR);
	void initScene();			//初始化场景
	void slotAddLineItem(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos);		//在场景中加入一个直线
	void drawChessBoard();		//绘制棋盘
	void drawCross(qreal xbias, qreal ybias, int isLeftRight);			//绘制卒炮位置
	void slotAddTextItem(qreal xpos, qreal ypos, QString text, int size, int rotation);
	void drawChessPieces(ChessPieces *chessPieces);
	void drawChessPiecesBackGround(int board_x, int board_y);		//绘制棋子背景
	void drawChessPiecesText(int board_x, int board_y, QString text, bool isRotation);		//绘制棋子文字
	void drawChessPiece(int board_x, int board_y, int piece, bool isRotation);			//绘制棋子背景和文字
	void drawPieceSelectRect(int board_x, int board_y, int style);					//绘制棋子选择的框
	void removePieceSelectRect(int style);				//移除棋子选择的框
private:
	QGraphicsScene *scene;		//定义一个场景对象指针
	QGraphicsView *view;
	int perWidth;				//棋盘一格的宽度、高度
	ChessPieces *chessPieces;	//棋子布局数据
	bool hasSelectPiece = false;		//是否已经选择了棋子
	QPoint selectPiecePostion;			//已经选择的棋子的位置
	int selectPiece;					//已经选择的棋子
	QGraphicsLineItem *pieceSelectLineItems[16] = {0};			//棋子选择方框，8个为一组

	//QLabel *mousePointLabel;        //---显示鼠标位置
	//QLabel *statusLabel;                //---显示鼠标移动时的实时位置 
};


