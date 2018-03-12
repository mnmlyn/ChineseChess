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
	bool whoseTurn;	//���ı���
	int chesspieces[9][10] = { 0 };//���Ӳ���
	QPoint masterPos[2];				//�洢��˧λ�ã�Ϊ(-1,-1)ʱ����˧���Ե��ˡ�0�洢�ҷ���1�洢�Է�
public:
	ChessPieces();
	int getPiece(int xpos, int ypos);//��ȡλ���ϵ�����
	bool getWhoseTurn();			//��ȡ���ı�����
	bool doStep(QPoint start, QPoint end);	//ִ��һ������
	bool isPosInBoard(int x, int y);	//�ж�λ���Ƿ���������
};


class ChineseChess : public QMainWindow
{
	Q_OBJECT

protected:
	void mousePressEvent(QMouseEvent *event);
public:
	ChineseChess(QWidget *parent = Q_NULLPTR);
	void initScene();			//��ʼ������
	void slotAddLineItem(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos);		//�ڳ����м���һ��ֱ��
	void drawChessBoard();		//��������
	void drawCross(qreal xbias, qreal ybias, int isLeftRight);			//��������λ��
	void slotAddTextItem(qreal xpos, qreal ypos, QString text, int size, int rotation);
	void drawChessPieces(ChessPieces *chessPieces);
	void drawChessPiecesBackGround(int board_x, int board_y);		//�������ӱ���
	void drawChessPiecesText(int board_x, int board_y, QString text, bool isRotation);		//������������
	void drawChessPiece(int board_x, int board_y, int piece, bool isRotation);			//�������ӱ���������
	void drawPieceSelectRect(int board_x, int board_y, int style);					//��������ѡ��Ŀ�
	void removePieceSelectRect(int style);				//�Ƴ�����ѡ��Ŀ�
private:
	QGraphicsScene *scene;		//����һ����������ָ��
	QGraphicsView *view;
	int perWidth;				//����һ��Ŀ�ȡ��߶�
	ChessPieces *chessPieces;	//���Ӳ�������
	bool hasSelectPiece = false;		//�Ƿ��Ѿ�ѡ��������
	QPoint selectPiecePostion;			//�Ѿ�ѡ������ӵ�λ��
	int selectPiece;					//�Ѿ�ѡ�������
	QGraphicsLineItem *pieceSelectLineItems[16] = {0};			//����ѡ�񷽿�8��Ϊһ��

	//QLabel *mousePointLabel;        //---��ʾ���λ��
	//QLabel *statusLabel;                //---��ʾ����ƶ�ʱ��ʵʱλ�� 
};


