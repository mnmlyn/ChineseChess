#pragma execution_character_set("utf-8")//�����������
#include "ChineseChess.h"

ChineseChess::ChineseChess(QWidget *parent)
	: QMainWindow(parent)
{
	scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 600, 600);
	initScene();		//��ʼ������
	view = new QGraphicsView;
	view->setScene(scene);
	view->setMinimumSize(600, 600);
	view->setStyleSheet("background:#D5912B;");
	view->show();
	setCentralWidget(view);		//����ͼview�����������ڵ�����
	resize(650, 650);			//���������ڳߴ�
	setWindowTitle("�й�����");
}

void ChineseChess::initScene()
{
	//��������
	drawChessBoard();

	//��������
	chessPieces = new ChessPieces();
	drawChessPieces(chessPieces);
}

/*
* �ڳ���������һ��ֱ��
*/
void ChineseChess::slotAddLineItem(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos)
{
	QGraphicsLineItem *item = new QGraphicsLineItem(QLineF(x1pos, y1pos, x2pos, y2pos));
	QPen pen = item->pen();
	pen.setColor(QColor(0, 160, 230));
	pen.setWidth(3);
	item->setPen(pen);
	scene->addItem(item);
	//item->setPos(0, 0);
}

/*
* ��������
*/
void ChineseChess::drawChessBoard()
{
	int i;
	qreal height = scene->sceneRect().height();
	perWidth = height / 9.0;	//�߶�
	//scene->sceneRect().width()
	//����
	for (i = 0; i < 10; i++)
	{
		slotAddLineItem(0, i*perWidth, 8 * perWidth, i*perWidth);
	}
	//����߿�
	slotAddLineItem(0, 0, 0, 9 * perWidth);
	slotAddLineItem(8*perWidth, 0, 8 * perWidth, 9 * perWidth);
	//��������-��
	for (i = 1; i < 8; i++)
	{
		slotAddLineItem(i * perWidth, 0, i * perWidth, 4 * perWidth);
	}
	//��������-��
	for (i = 1; i < 8; i++)
	{
		slotAddLineItem(i * perWidth, 5* perWidth, i * perWidth, 9 * perWidth);
	}
	//ʿб��
	slotAddLineItem(3 * perWidth, 0, 5 * perWidth, 2 * perWidth);
	slotAddLineItem(3 * perWidth, 2 * perWidth, 5 * perWidth, 0);
	slotAddLineItem(3 * perWidth, 7 * perWidth, 5 * perWidth, 9 * perWidth);
	slotAddLineItem(3 * perWidth, 9 * perWidth, 5 * perWidth, 7 * perWidth);
	//����λ�ñ�ʶ
	//��
	drawCross(perWidth, 2 * perWidth, 0);
	drawCross(7 * perWidth, 2 * perWidth, 0);
	drawCross(perWidth, 7 * perWidth, 0);
	drawCross(7 * perWidth, 7 * perWidth, 0);
	//��
	drawCross(0 * perWidth, 3 * perWidth, 1);
	drawCross(2 * perWidth, 3 * perWidth, 0);
	drawCross(4 * perWidth, 3 * perWidth, 0);
	drawCross(6 * perWidth, 3 * perWidth, 0);
	drawCross(8 * perWidth, 3 * perWidth, -1);
	//��
	drawCross(0 * perWidth, 6 * perWidth, 1);
	drawCross(2 * perWidth, 6 * perWidth, 0);
	drawCross(4 * perWidth, 6 * perWidth, 0);
	drawCross(6 * perWidth, 6 * perWidth, 0);
	drawCross(8 * perWidth, 6 * perWidth, -1);
	//���Ӻ���
	int fontSize = (int)(perWidth / 1.46);
	slotAddTextItem(1 * perWidth, 5 * perWidth, "��", fontSize, -90);
	slotAddTextItem(2.5 * perWidth, 5 * perWidth, "��", fontSize, -90);
	slotAddTextItem(7 * perWidth, 4 * perWidth, "��", fontSize, 90);
	slotAddTextItem(5.5 * perWidth, 4 * perWidth, "��", fontSize, 90);
}

/*
* ��������λ�ñ�ʶ��isLeftRight=0����ȫͼ�Σ�<0������룬>0�����Ұ�
*/
void ChineseChess::drawCross(qreal xbias, qreal ybias,int isLeftRight)
{
	qreal ds = 8.0, de = 4.0;//��������λ�ñ�ʶ�Ķ��ߵĳ��ȣ�ֵ������ӿ�ȵķ�֮��
	//�Ұ�
	if (isLeftRight >= 0)
	{
		//��
		slotAddLineItem(xbias + perWidth / ds, ybias + perWidth / ds, xbias + perWidth / ds, ybias + perWidth / de);
		slotAddLineItem(xbias + perWidth / ds, ybias + perWidth / ds, xbias + perWidth / de, ybias + perWidth / ds);

		//��
		slotAddLineItem(xbias + perWidth / ds, ybias - perWidth / ds, xbias + perWidth / ds, ybias - perWidth / de);
		slotAddLineItem(xbias + perWidth / ds, ybias - perWidth / ds, xbias + perWidth / de, ybias - perWidth / ds);
	}
	//���
	if (isLeftRight <= 0)
	{
		//��
		slotAddLineItem(xbias - perWidth / ds, ybias + perWidth / ds, xbias - perWidth / ds, ybias + perWidth / de);
		slotAddLineItem(xbias - perWidth / ds, ybias + perWidth / ds, xbias - perWidth / de, ybias + perWidth / ds);

		//��
		slotAddLineItem(xbias - perWidth / ds, ybias - perWidth / ds, xbias - perWidth / ds, ybias - perWidth / de);
		slotAddLineItem(xbias - perWidth / ds, ybias - perWidth / ds, xbias - perWidth / de, ybias - perWidth / ds);
	}
}

/*
* �ڳ��������һ������
*/
void ChineseChess::slotAddTextItem(qreal xpos,qreal ypos,QString text,int size,int rotation)
{
	QFont font("Times", size);
	QGraphicsTextItem *item = new QGraphicsTextItem(text);
	item->setFont(font);
	//item->setFlag(QGraphicsItem::ItemIsMovable);
	item->setDefaultTextColor(QColor(0, 160, 230));
	item->setRotation(rotation);
	scene->addItem(item);
	item->setPos(xpos, ypos);
}

/*
* ������������
*/
void ChineseChess::drawChessPieces(ChessPieces *chessPieces)
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			int piece = chessPieces->getPiece(i, j);
			if (0 == piece)continue;//�˴�û������
			
			drawChessPiece(i, j, piece, piece < 0);

		}
	}
}

/*
* ������������
*/
void ChineseChess::drawChessPiecesText(int board_x, int board_y, QString text, bool isRotation)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//λ�ò���������Чλ��
	qreal xpos = board_x * perWidth;
	qreal ypos = board_y * perWidth;
	QFont font("Times", (int)(perWidth / 2.2));
	QGraphicsTextItem *item = new QGraphicsTextItem(text);
	item->setFont(font);
	//item->setFlag(QGraphicsItem::ItemIsMovable);
	if (isRotation)
	{
		item->setDefaultTextColor(QColor(0, 0, 255));
		item->setRotation(180);
		item->setPos(xpos + perWidth * 0.4, ypos + perWidth * 0.4);
	}
	else
	{
		item->setDefaultTextColor(QColor(255, 0, 0));
		item->setPos(xpos - perWidth * 0.4, ypos - perWidth * 0.4);
	}
	scene->addItem(item);
}

/*
* �������ӱ���
*/
void ChineseChess::drawChessPiecesBackGround(int board_x, int board_y)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//λ�ò���������Чλ��
	qreal xpos = board_x * perWidth;
	qreal ypos = board_y * perWidth;
	QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(-0.4*perWidth, -0.4*perWidth, 0.8*perWidth, 0.8*perWidth));
	item->setPen(Qt::NoPen);
	item->setBrush(QColor(128, 128, 128));
	//item->setFlag(QGraphicsItem::ItemIsSelectable);
	scene->addItem(item);
	item->setPos(xpos,ypos);
}

/*
* �������ӱ���������
*/
void ChineseChess::drawChessPiece(int board_x, int board_y, int piece, bool isRotation)
{
	const QString piece2text[] = { "",
		"��",	"��",	"��",	"��",	"��",
		//1		2		3		4		5
		"܇",	"�R",
		//6		7
		"��",	"ʿ",	"��",	"��",	"�h",
		//8		9		10		11		12
		"܇",	"�R",
		//13	14
	};
	if (piece > 0 && piece < 8)//�ҷ�����
	{
		drawChessPiecesBackGround(board_x, board_y);
		drawChessPiecesText(board_x, board_y, piece2text[piece], false);
	}
	else if (piece < 0 && piece > -8)//�Է����ӣ���܇��
	{
		drawChessPiecesBackGround(board_x, board_y);
		drawChessPiecesText(board_x, board_y, piece2text[7-piece], true);
	}
}

/*
* ������¼�����
*/
void ChineseChess::mousePressEvent(QMouseEvent *e)
{
	QPoint viewPoint = e->pos();
	QPointF scenePoint = view->mapToScene(viewPoint);//��view���꣨���������꣩��ת��Ϊscene��������
	//�������λ�ã�ת��Ϊ��������
	int board_x, board_y;
	board_x = (scenePoint.x() + perWidth / 2.0) / perWidth;
	board_y = (scenePoint.y() + perWidth / 2.0) / perWidth;
	int piece = chessPieces->getPiece(board_x, board_y);//��õ��λ�õ�����
	if (piece > 0 && chessPieces->getWhoseTurn() || //���ҷ�����ѡ�����ҷ�����
		piece < 0 && !chessPieces->getWhoseTurn()	//�öԷ�����ѡ���˶Է�����
		)
	{
		//ѡ��˴�����
		removePieceSelectRect(0);//�������ѡ���
		removePieceSelectRect(1);//�������ѡ���
		drawPieceSelectRect(board_x, board_y, 1);//��������ѡ���

		this->hasSelectPiece = true;
		this->selectPiecePostion = QPoint(board_x, board_y);
		this->selectPiece = piece;
	}
	else if (this->hasSelectPiece &&	//�Ѿ�ѡ��������
		chessPieces->doStep(this->selectPiecePostion,QPoint(board_x,board_y))	//����������ִ��������
		)
	{
		qreal xpos, ypos;
		xpos = this->selectPiecePostion.x() * perWidth;
		ypos = this->selectPiecePostion.y() * perWidth;
		//�Ƴ���λ���ϵ�item
		QTransform transform;
		QGraphicsItem *item;
		item = scene->itemAt(xpos, ypos, transform);
		scene->removeItem(item);
		item = scene->itemAt(xpos, ypos, transform);
		scene->removeItem(item);

		//�����λ���������ӣ�Ӧ�����Ƴ�
		if (piece)
		{
			item = scene->itemAt(board_x * perWidth, board_y * perWidth, transform);
			scene->removeItem(item);
			item = scene->itemAt(board_x * perWidth, board_y * perWidth, transform);
			scene->removeItem(item);
		}

		//������λ������
		drawChessPiece(board_x, board_y, this->selectPiece, this->selectPiece < 0);
		drawPieceSelectRect(board_x, board_y, 0);//��������ѡ���

		this->hasSelectPiece = false;
	}

}

/*
* ��������ѡ��Ŀ�
*/
void ChineseChess::drawPieceSelectRect(int board_x, int board_y, int style)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//λ�ò���������Чλ��
	//��������λ��
	qreal x = board_x * perWidth;
	qreal y = board_y * perWidth;
	//�߶���Զ�������˾����������ĵĺ��ݾ���
	qreal dmax = perWidth * 0.5;
	qreal dmin = perWidth * 0.3;

	//style==0�ķ��򣬴���pieceSelectLineItems��ǰ8��λ��
	//style==1�ķ��򣬴���pieceSelectLineItems�ĺ�8��λ��
	if (style != 0 && style != 1)return;
	int style_bias = 0;
	if(style == 1)style_bias = 8;

	//������ת����ѡ��ѡ����������
	for (int i = 0 + style_bias; i < 4 + style_bias; i++)
	{
		pieceSelectLineItems[i] = new QGraphicsLineItem(QLineF(- dmax, - dmax, - dmax, - dmin));//��������
		QPen pen = pieceSelectLineItems[i]->pen();
		if(style == 1)pen.setColor(QColor(255, 60, 230));
		else if (style == 0)pen.setColor(QColor(60, 255, 230));
		pen.setWidth(3);
		pieceSelectLineItems[i]->setPen(pen);
		pieceSelectLineItems[i]->setRotation(90 * (i % 4));
		pieceSelectLineItems[i]->setPos(x, y);
		scene->addItem(pieceSelectLineItems[i]);
	}
	//������ת����ѡ��ѡ��������������
	for (int i = 4 + style_bias; i < 8 + style_bias; i++)
	{
		pieceSelectLineItems[i] = new QGraphicsLineItem(QLineF(- dmax, - dmax, - dmin, - dmax));//��������
		QPen pen = pieceSelectLineItems[i]->pen();
		if (style == 1)pen.setColor(QColor(255, 60, 230));
		else if (style == 0)pen.setColor(QColor(60, 255, 230));
		pen.setWidth(3);
		pieceSelectLineItems[i]->setPen(pen);
		pieceSelectLineItems[i]->setRotation(90 * (i % 4));
		pieceSelectLineItems[i]->setPos(x, y);
		scene->addItem(pieceSelectLineItems[i]);
	}


}

/*
* �Ƴ�����ѡ��Ŀ�
*/
void ChineseChess::removePieceSelectRect(int style)
{
	int style_bias = 0;
	if(style == 1)style_bias = 8;
	for (int i = 0 + style_bias; i < 8 + style_bias; i++)
	{
		if(pieceSelectLineItems[i] != 0)scene->removeItem(pieceSelectLineItems[i]);
	}
}

////////////////////////////////////////////////////////////////����///////////////
ChessPieces::ChessPieces()
{
	whoseTurn = true;
	this->masterPos[0] = QPoint(4, 9);//�ҷ�˧��λ��
	this->masterPos[1] = QPoint(4, 0);//�Է�����λ��

	//�Է�����һ������
	chesspieces[0][0] = -6;
	chesspieces[1][0] = -7;
	chesspieces[2][0] = -3;
	chesspieces[3][0] = -2;
	chesspieces[4][0] = -1;
	chesspieces[5][0] = -2;
	chesspieces[6][0] = -3;
	chesspieces[7][0] = -7;
	chesspieces[8][0] = -6;
	//�Է���
	chesspieces[1][2] = -5;
	chesspieces[7][2] = -5;
	//�Է���
	chesspieces[0][3] = -4;
	chesspieces[2][3] = -4;
	chesspieces[4][3] = -4;
	chesspieces[6][3] = -4;
	chesspieces[8][3] = -4;

	//�ҷ�����һ������
	chesspieces[0][9] = 6;
	chesspieces[1][9] = 7;
	chesspieces[2][9] = 3;
	chesspieces[3][9] = 2;
	chesspieces[4][9] = 1;
	chesspieces[5][9] = 2;
	chesspieces[6][9] = 3;
	chesspieces[7][9] = 7;
	chesspieces[8][9] = 6;
	//�ҷ���
	chesspieces[1][7] = 5;
	chesspieces[7][7] = 5;
	//�ҷ���
	chesspieces[0][6] = 4;
	chesspieces[2][6] = 4;
	chesspieces[4][6] = 4;
	chesspieces[6][6] = 4;
	chesspieces[8][6] = 4;
}

/*
* ��ȡλ���ϵ�����
*/
int ChessPieces::getPiece(int board_x, int board_y)
{
	if (!this->isPosInBoard(board_x, board_y))return 0;//����������������
	return this->chesspieces[board_x][board_y];
}

/*
* ��ȡ���ķ�����
*/
bool ChessPieces::getWhoseTurn()
{
	return this->whoseTurn;
}

/*
* ��ǰλ���Ƿ��������ϣ�������������
*/
bool ChessPieces::isPosInBoard(int board_x, int board_y)
{
	if (board_x > 8 || board_x < 0 || board_y < 0 || board_y > 9)return false;//�������ʼ����ֹλ�ò��������ϣ�����false
	else return true;
}

/*
* ִ��һ������
* �ж��Ƿ���Ϲ��򣬷��������岢����true
*/
bool ChessPieces::doStep(QPoint start, QPoint end)
{
	//�ж�����
	if (this->masterPos[0] == QPoint(-1, -1) || this->masterPos[1] == QPoint(-1, -1))return false;//��˧�Ѿ����ԣ�����

	if (start == end)return false;//��ʼ����ֹλ��һ����ֱ�ӷ���
	if (!this->isPosInBoard(start.x(), start.y())
		|| !this->isPosInBoard(end.x(), end.y()))
		return false;//�������ʼ����ֹλ�ò��������ϣ�ֱ�ӷ���
	int startPiece = this->chesspieces[start.x()][start.y()];
	int endPiece = this->chesspieces[end.x()][end.y()];
	if (this->whoseTurn && startPiece > 0 && endPiece <= 0	//�ֵ��ҷ����壬����ʼλ��Ϊ�ҷ����ӣ�����λ�ò����ҷ�����
		||
		!this->whoseTurn && startPiece < 0 && endPiece >= 0	//�ֵ��Է����壬����ʼλ��Ϊ�Է����ӣ�����λ�ò��ǶԷ�����
		)
	{
		//�жϹ���д������

		int i,max,min,count=0;
		
		//�ݲ����ǽ�˧��������
		//ֻ����ֱ�ߵ�����
		if (startPiece == 6 || startPiece == -6 ||	//܇
			startPiece == 5 || startPiece == -5 ||	//��
			startPiece == 4 || startPiece == -4 ||	//����
			startPiece == 1 || startPiece == -1		//��˧
			)
		{
			if (start.x() != end.x() && start.y() != end.y())//ֻ����ֱ��
				return false;
			else if (start.x() == end.x() && start.y() != end.y())//�����ߵ����
			{
				min = start.y() < end.y() ? start.y() : end.y();
				max = start.y() > end.y() ? start.y() : end.y();
				if ((startPiece == 4 || startPiece == -4 ||	//����
					startPiece == 1 || startPiece == -1		//��˧
					)
					&& max - min != 1)//���佫˧ֻ����һ��
					return false;
				if (startPiece == 4 && end.y() > start.y()
					|| startPiece == -4 && end.y() < start.y()
					)//���䲻�ܺ���
					return false;
				if (startPiece == 1 && end.y() < 7
					|| startPiece == -1 && end.y() > 2
					)//��˧����Խ����������
					return false;
				for (i = min + 1; i < max; i++)
				{
					if (this->getPiece(start.x(), i))//�м������������
						if (startPiece == 6 || startPiece == -6)//܇
							return false;//�м䲻�������������
						else if (startPiece == 5 || startPiece == -5)
						{
							count++;
							if (count > 1)return false;//���м�ֻ����һ������
						}
				}
				//�ڲ���ֱ�ӳ��ӣ����ܿմ�
				if (startPiece == 5 || startPiece == -5)
					if(count == 0 && endPiece != 0//û���ڼ���
						|| count == 1 && endPiece == 0)//��������Ծ����
						return false;
			}
			else if (start.x() != end.x() && start.y() == end.y())//�ߺ��ߵ����
			{
				min = start.x() < end.x() ? start.x() : end.x();
				max = start.x() > end.x() ? start.x() : end.x();
				if ((startPiece == 4 || startPiece == -4 ||	//����
					startPiece == 1 || startPiece == -1		//��˧
					)
					&& max - min != 1)//���佫˧ֻ����һ��
					return false;
				if (startPiece == 4 && start.y() > 4
					|| startPiece == -4 && start.y() < 5
					)//������˺Ӳ��ܺ���
					return false;
				if ((startPiece == 1 || startPiece == -1)
					&& (end.x() < 3 || end.x() > 5)
					)//��˧���ܳ��м�������
					return false;
				for (i = min + 1; i < max; i++)
				{
					if (this->getPiece(i, start.y()))//�м������������
						if (startPiece == 6 || startPiece == -6)//܇
							return false;//�м䲻�������������
						else if (startPiece == 5 || startPiece == -5)
						{
							count++;
							if (count > 1)return false;//���м�ֻ����һ������
						}
				}
				//�ڲ���ֱ�ӳ��ӣ����ܿմ�
				if (startPiece == 5 || startPiece == -5)
					if (count == 0 && endPiece != 0//û���ڼ���
						|| count == 1 && endPiece == 0)//��������Ծ����
						return false;
			}
		}

		//��
		if (startPiece == 3 || startPiece == -3)
		{
			if (abs(start.x() - end.x()) != 2 || abs(start.y() - end.y()) != 2)//�ߵĲ�����
				return false;
			if (startPiece == -3 && end.y() > 4
				|| startPiece == 3 && end.y() < 5
				)//���ܹ���
				return false;
			if (this->getPiece((start.x() + end.x()) / 2, (start.y() + end.y()) / 2))//��·�߱���ס
				return false;
		}

		//��
		if (startPiece == 7 || startPiece == -7)
		{
			if (
				!(abs(start.x() - end.x()) == 2 && abs(start.y() - end.y()) == 1
					|| abs(start.x() - end.x()) == 1 && abs(start.y() - end.y()) == 2)
				)//������
				return false;
			if (abs(start.x() - end.x()) == 2 && this->getPiece((start.x() + end.x()) / 2, start.y())//����ߣ����ȱ���
				|| abs(start.y() - end.y()) == 2 && this->getPiece(start.x(), (start.y() + end.y()) / 2)//�����ߣ����ȱ���
				)
				return false;
		}

		//ʿ
		if (startPiece == 2 || startPiece == -2)
		{
			if (abs(start.x() - end.x()) != 1 || abs(start.y() - end.y()) != 1)//�ߵĲ���б��
				return false;
			if (startPiece == 2 && end.y() < 7
				|| startPiece == -2 && end.y() > 2
				)//ʿ����Խ����������
				return false;
			if (end.x() < 3 || end.x() > 5)//ʿ���ܳ��м�������
				return false;
		}

		//��˧���ܼ���
		if (this->masterPos[0].x() == this->masterPos[1].x()//��˧һ����
			&& abs(startPiece) != 1//�ƶ��Ĳ��ǽ�˧
			&& start.x() == this->masterPos[0].x()//�ƶ������뽫˧һ����
			&& start.y() > this->masterPos[1].y()//�ƶ������ڽ�˧֮��
			&& start.y() < this->masterPos[0].y()//�ƶ������ڽ�˧֮��
			)
		{
			count = 0;
			for (i = this->masterPos[1].y() + 1; i < this->masterPos[0].y(); i++)
			{
				if (this->getPiece(this->masterPos[0].x(), i))//�м������������
				{
					count++;
				}
			}
			if (count < 2 //��˧֮��ֻ��һ������
				&& (
					end.x() != start.x() //Ҫ���Ƶ�������·
					|| end.y() < this->masterPos[1].y() //Ҫ���ƶ�����˧֮��
					|| end.y() > this->masterPos[0].y()//Ҫ���ƶ�����˧֮��
					)
				)
				return false;
		}
		if (startPiece == 1)//�ƶ��ҷ�˧
		{
			if (end.x() == this->masterPos[1].x())//�ƶ�����λ�ã���Է���ͬһ����
			{
				count = 0;
				for (i = this->masterPos[1].y() + 1; i < end.y(); i++)
				{
					if (this->getPiece(this->masterPos[1].x(), i))//�м������������
					{
						count++;
					}
				}
				if (count < 1)return false;//�ƶ�֮�󣬽�˧֮�������ӣ��ʲ����ƶ�
			}
			this->masterPos[0] = end;//�����ҷ�˧��λ��
		}
		if (startPiece == -1)//�ƶ��Է���
		{
			if (end.x() == this->masterPos[0].x())//�ƶ�����λ�ã����ҷ�˧ͬһ����
			{
				count = 0;
				for (i = end.y() + 1; i < this->masterPos[0].y(); i++)
				{
					if (this->getPiece(this->masterPos[0].x(), i))//�м������������
					{
						count++;
					}
				}
				if (count < 1)return false;//�ƶ�֮�󣬽�˧֮�������ӣ��ʲ����ƶ�
			}
			this->masterPos[1] = end;//���¶Է�����λ��
		}

		//��˧���Ե�
		if (endPiece == 1)
		{
			this->masterPos[0] = QPoint(-1, -1);
		}
		if (endPiece == -1)
		{
			this->masterPos[1] = QPoint(-1, -1);
		}

		//������������
		this->chesspieces[end.x()][end.y()] = this->chesspieces[start.x()][start.y()];
		this->chesspieces[start.x()][start.y()] = 0;
		this->whoseTurn = !this->whoseTurn;
		//����true
		return true;
		
	}
	return false;
}

