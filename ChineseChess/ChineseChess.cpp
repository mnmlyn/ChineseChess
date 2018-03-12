#pragma execution_character_set("utf-8")//解决中文乱码
#include "ChineseChess.h"

ChineseChess::ChineseChess(QWidget *parent)
	: QMainWindow(parent)
{
	scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 600, 600);
	initScene();		//初始化场景
	view = new QGraphicsView;
	view->setScene(scene);
	view->setMinimumSize(600, 600);
	view->setStyleSheet("background:#D5912B;");
	view->show();
	setCentralWidget(view);		//将试图view设置在主窗口的中央
	resize(650, 650);			//调整主窗口尺寸
	setWindowTitle("中国羊棋");
}

void ChineseChess::initScene()
{
	//绘制棋盘
	drawChessBoard();

	//绘制棋子
	chessPieces = new ChessPieces();
	drawChessPieces(chessPieces);
}

/*
* 在场景中增加一条直线
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
* 绘制棋盘
*/
void ChineseChess::drawChessBoard()
{
	int i;
	qreal height = scene->sceneRect().height();
	perWidth = height / 9.0;	//高度
	//scene->sceneRect().width()
	//横线
	for (i = 0; i < 10; i++)
	{
		slotAddLineItem(0, i*perWidth, 8 * perWidth, i*perWidth);
	}
	//竖向边框
	slotAddLineItem(0, 0, 0, 9 * perWidth);
	slotAddLineItem(8*perWidth, 0, 8 * perWidth, 9 * perWidth);
	//竖向内线-上
	for (i = 1; i < 8; i++)
	{
		slotAddLineItem(i * perWidth, 0, i * perWidth, 4 * perWidth);
	}
	//竖向内线-下
	for (i = 1; i < 8; i++)
	{
		slotAddLineItem(i * perWidth, 5* perWidth, i * perWidth, 9 * perWidth);
	}
	//士斜线
	slotAddLineItem(3 * perWidth, 0, 5 * perWidth, 2 * perWidth);
	slotAddLineItem(3 * perWidth, 2 * perWidth, 5 * perWidth, 0);
	slotAddLineItem(3 * perWidth, 7 * perWidth, 5 * perWidth, 9 * perWidth);
	slotAddLineItem(3 * perWidth, 9 * perWidth, 5 * perWidth, 7 * perWidth);
	//卒炮位置标识
	//炮
	drawCross(perWidth, 2 * perWidth, 0);
	drawCross(7 * perWidth, 2 * perWidth, 0);
	drawCross(perWidth, 7 * perWidth, 0);
	drawCross(7 * perWidth, 7 * perWidth, 0);
	//卒
	drawCross(0 * perWidth, 3 * perWidth, 1);
	drawCross(2 * perWidth, 3 * perWidth, 0);
	drawCross(4 * perWidth, 3 * perWidth, 0);
	drawCross(6 * perWidth, 3 * perWidth, 0);
	drawCross(8 * perWidth, 3 * perWidth, -1);
	//兵
	drawCross(0 * perWidth, 6 * perWidth, 1);
	drawCross(2 * perWidth, 6 * perWidth, 0);
	drawCross(4 * perWidth, 6 * perWidth, 0);
	drawCross(6 * perWidth, 6 * perWidth, 0);
	drawCross(8 * perWidth, 6 * perWidth, -1);
	//楚河汉界
	int fontSize = (int)(perWidth / 1.46);
	slotAddTextItem(1 * perWidth, 5 * perWidth, "楚", fontSize, -90);
	slotAddTextItem(2.5 * perWidth, 5 * perWidth, "河", fontSize, -90);
	slotAddTextItem(7 * perWidth, 4 * perWidth, "汉", fontSize, 90);
	slotAddTextItem(5.5 * perWidth, 4 * perWidth, "界", fontSize, 90);
}

/*
* 绘制卒炮位置标识，isLeftRight=0绘制全图形，<0绘制左半，>0绘制右半
*/
void ChineseChess::drawCross(qreal xbias, qreal ybias,int isLeftRight)
{
	qreal ds = 8.0, de = 4.0;//控制卒炮位置标识的短线的长度，值代表格子宽度的分之几
	//右半
	if (isLeftRight >= 0)
	{
		//下
		slotAddLineItem(xbias + perWidth / ds, ybias + perWidth / ds, xbias + perWidth / ds, ybias + perWidth / de);
		slotAddLineItem(xbias + perWidth / ds, ybias + perWidth / ds, xbias + perWidth / de, ybias + perWidth / ds);

		//上
		slotAddLineItem(xbias + perWidth / ds, ybias - perWidth / ds, xbias + perWidth / ds, ybias - perWidth / de);
		slotAddLineItem(xbias + perWidth / ds, ybias - perWidth / ds, xbias + perWidth / de, ybias - perWidth / ds);
	}
	//左半
	if (isLeftRight <= 0)
	{
		//下
		slotAddLineItem(xbias - perWidth / ds, ybias + perWidth / ds, xbias - perWidth / ds, ybias + perWidth / de);
		slotAddLineItem(xbias - perWidth / ds, ybias + perWidth / ds, xbias - perWidth / de, ybias + perWidth / ds);

		//上
		slotAddLineItem(xbias - perWidth / ds, ybias - perWidth / ds, xbias - perWidth / ds, ybias - perWidth / de);
		slotAddLineItem(xbias - perWidth / ds, ybias - perWidth / ds, xbias - perWidth / de, ybias - perWidth / ds);
	}
}

/*
* 在场景中添加一个字体
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
* 绘制所有棋子
*/
void ChineseChess::drawChessPieces(ChessPieces *chessPieces)
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			int piece = chessPieces->getPiece(i, j);
			if (0 == piece)continue;//此处没有棋子
			
			drawChessPiece(i, j, piece, piece < 0);

		}
	}
}

/*
* 绘制棋子文字
*/
void ChineseChess::drawChessPiecesText(int board_x, int board_y, QString text, bool isRotation)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//位置不是棋盘有效位置
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
* 绘制棋子背景
*/
void ChineseChess::drawChessPiecesBackGround(int board_x, int board_y)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//位置不是棋盘有效位置
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
* 绘制棋子背景和文字
*/
void ChineseChess::drawChessPiece(int board_x, int board_y, int piece, bool isRotation)
{
	const QString piece2text[] = { "",
		"帥",	"仕",	"洋",	"兵",	"炮",
		//1		2		3		4		5
		"車",	"馬",
		//6		7
		"將",	"士",	"羊",	"卒",	"砲",
		//8		9		10		11		12
		"車",	"馬",
		//13	14
	};
	if (piece > 0 && piece < 8)//我方棋子
	{
		drawChessPiecesBackGround(board_x, board_y);
		drawChessPiecesText(board_x, board_y, piece2text[piece], false);
	}
	else if (piece < 0 && piece > -8)//对方棋子，除車马
	{
		drawChessPiecesBackGround(board_x, board_y);
		drawChessPiecesText(board_x, board_y, piece2text[7-piece], true);
	}
}

/*
* 鼠标点击事件处理
*/
void ChineseChess::mousePressEvent(QMouseEvent *e)
{
	QPoint viewPoint = e->pos();
	QPointF scenePoint = view->mapToScene(viewPoint);//将view坐标（即窗口坐标），转换为scene场景坐标
	//将鼠标点击位置，转换为棋盘坐标
	int board_x, board_y;
	board_x = (scenePoint.x() + perWidth / 2.0) / perWidth;
	board_y = (scenePoint.y() + perWidth / 2.0) / perWidth;
	int piece = chessPieces->getPiece(board_x, board_y);//获得点击位置的棋子
	if (piece > 0 && chessPieces->getWhoseTurn() || //该我方走且选择了我方棋子
		piece < 0 && !chessPieces->getWhoseTurn()	//该对方走且选择了对方棋子
		)
	{
		//选择此处棋子
		removePieceSelectRect(0);//清除已有选择框
		removePieceSelectRect(1);//清除已有选择框
		drawPieceSelectRect(board_x, board_y, 1);//绘制棋子选择框

		this->hasSelectPiece = true;
		this->selectPiecePostion = QPoint(board_x, board_y);
		this->selectPiece = piece;
	}
	else if (this->hasSelectPiece &&	//已经选择了棋子
		chessPieces->doStep(this->selectPiecePostion,QPoint(board_x,board_y))	//可以走棋且执行了走棋
		)
	{
		qreal xpos, ypos;
		xpos = this->selectPiecePostion.x() * perWidth;
		ypos = this->selectPiecePostion.y() * perWidth;
		//移除旧位置上的item
		QTransform transform;
		QGraphicsItem *item;
		item = scene->itemAt(xpos, ypos, transform);
		scene->removeItem(item);
		item = scene->itemAt(xpos, ypos, transform);
		scene->removeItem(item);

		//如果新位置上有棋子，应该先移除
		if (piece)
		{
			item = scene->itemAt(board_x * perWidth, board_y * perWidth, transform);
			scene->removeItem(item);
			item = scene->itemAt(board_x * perWidth, board_y * perWidth, transform);
			scene->removeItem(item);
		}

		//绘制新位置棋子
		drawChessPiece(board_x, board_y, this->selectPiece, this->selectPiece < 0);
		drawPieceSelectRect(board_x, board_y, 0);//绘制棋子选择框

		this->hasSelectPiece = false;
	}

}

/*
* 绘制棋子选择的框
*/
void ChineseChess::drawPieceSelectRect(int board_x, int board_y, int style)
{
	if (!chessPieces->isPosInBoard(board_x, board_y))return;//位置不是棋盘有效位置
	//棋子中心位置
	qreal x = board_x * perWidth;
	qreal y = board_y * perWidth;
	//线段最远（近）端距离棋子中心的横纵距离
	qreal dmax = perWidth * 0.5;
	qreal dmin = perWidth * 0.3;

	//style==0的方框，存在pieceSelectLineItems的前8个位置
	//style==1的方框，存在pieceSelectLineItems的后8个位置
	if (style != 0 && style != 1)return;
	int style_bias = 0;
	if(style == 1)style_bias = 8;

	//依靠旋转绘制选择选择框的四条线
	for (int i = 0 + style_bias; i < 4 + style_bias; i++)
	{
		pieceSelectLineItems[i] = new QGraphicsLineItem(QLineF(- dmax, - dmax, - dmax, - dmin));//左上竖线
		QPen pen = pieceSelectLineItems[i]->pen();
		if(style == 1)pen.setColor(QColor(255, 60, 230));
		else if (style == 0)pen.setColor(QColor(60, 255, 230));
		pen.setWidth(3);
		pieceSelectLineItems[i]->setPen(pen);
		pieceSelectLineItems[i]->setRotation(90 * (i % 4));
		pieceSelectLineItems[i]->setPos(x, y);
		scene->addItem(pieceSelectLineItems[i]);
	}
	//依靠旋转绘制选择选择框的另外四条线
	for (int i = 4 + style_bias; i < 8 + style_bias; i++)
	{
		pieceSelectLineItems[i] = new QGraphicsLineItem(QLineF(- dmax, - dmax, - dmin, - dmax));//左上竖线
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
* 移除棋子选择的框
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

////////////////////////////////////////////////////////////////棋子///////////////
ChessPieces::ChessPieces()
{
	whoseTurn = true;
	this->masterPos[0] = QPoint(4, 9);//我方帅的位置
	this->masterPos[1] = QPoint(4, 0);//对方将的位置

	//对方底线一排棋子
	chesspieces[0][0] = -6;
	chesspieces[1][0] = -7;
	chesspieces[2][0] = -3;
	chesspieces[3][0] = -2;
	chesspieces[4][0] = -1;
	chesspieces[5][0] = -2;
	chesspieces[6][0] = -3;
	chesspieces[7][0] = -7;
	chesspieces[8][0] = -6;
	//对方炮
	chesspieces[1][2] = -5;
	chesspieces[7][2] = -5;
	//对方卒
	chesspieces[0][3] = -4;
	chesspieces[2][3] = -4;
	chesspieces[4][3] = -4;
	chesspieces[6][3] = -4;
	chesspieces[8][3] = -4;

	//我方底线一排棋子
	chesspieces[0][9] = 6;
	chesspieces[1][9] = 7;
	chesspieces[2][9] = 3;
	chesspieces[3][9] = 2;
	chesspieces[4][9] = 1;
	chesspieces[5][9] = 2;
	chesspieces[6][9] = 3;
	chesspieces[7][9] = 7;
	chesspieces[8][9] = 6;
	//我方炮
	chesspieces[1][7] = 5;
	chesspieces[7][7] = 5;
	//我方兵
	chesspieces[0][6] = 4;
	chesspieces[2][6] = 4;
	chesspieces[4][6] = 4;
	chesspieces[6][6] = 4;
	chesspieces[8][6] = 4;
}

/*
* 获取位置上的棋子
*/
int ChessPieces::getPiece(int board_x, int board_y)
{
	if (!this->isPosInBoard(board_x, board_y))return 0;//传入坐标在棋盘外
	return this->chesspieces[board_x][board_y];
}

/*
* 获取该哪方走棋
*/
bool ChessPieces::getWhoseTurn()
{
	return this->whoseTurn;
}

/*
* 当前位置是否在棋盘上，传入棋盘坐标
*/
bool ChessPieces::isPosInBoard(int board_x, int board_y)
{
	if (board_x > 8 || board_x < 0 || board_y < 0 || board_y > 9)return false;//传入的起始或终止位置不在棋盘上，返回false
	else return true;
}

/*
* 执行一步走棋
* 判断是否符合规则，符合则走棋并返回true
*/
bool ChessPieces::doStep(QPoint start, QPoint end)
{
	//判断终盘
	if (this->masterPos[0] == QPoint(-1, -1) || this->masterPos[1] == QPoint(-1, -1))return false;//将帅已经被吃，终盘

	if (start == end)return false;//起始和终止位置一样，直接返回
	if (!this->isPosInBoard(start.x(), start.y())
		|| !this->isPosInBoard(end.x(), end.y()))
		return false;//传入的起始或终止位置不在棋盘上，直接返回
	int startPiece = this->chesspieces[start.x()][start.y()];
	int endPiece = this->chesspieces[end.x()][end.y()];
	if (this->whoseTurn && startPiece > 0 && endPiece <= 0	//轮到我方走棋，且起始位置为我方棋子，结束位置不是我方棋子
		||
		!this->whoseTurn && startPiece < 0 && endPiece >= 0	//轮到对方走棋，且起始位置为对方棋子，结束位置不是对方棋子
		)
	{
		//判断规则写在这里

		int i,max,min,count=0;
		
		//暂不考虑将帅见面问题
		//只能走直线的棋子
		if (startPiece == 6 || startPiece == -6 ||	//車
			startPiece == 5 || startPiece == -5 ||	//炮
			startPiece == 4 || startPiece == -4 ||	//兵卒
			startPiece == 1 || startPiece == -1		//将帅
			)
		{
			if (start.x() != end.x() && start.y() != end.y())//只能走直线
				return false;
			else if (start.x() == end.x() && start.y() != end.y())//走竖线的情况
			{
				min = start.y() < end.y() ? start.y() : end.y();
				max = start.y() > end.y() ? start.y() : end.y();
				if ((startPiece == 4 || startPiece == -4 ||	//兵卒
					startPiece == 1 || startPiece == -1		//将帅
					)
					&& max - min != 1)//兵卒将帅只能走一步
					return false;
				if (startPiece == 4 && end.y() > start.y()
					|| startPiece == -4 && end.y() < start.y()
					)//兵卒不能后退
					return false;
				if (startPiece == 1 && end.y() < 7
					|| startPiece == -1 && end.y() > 2
					)//将帅不能越过后三条线
					return false;
				for (i = min + 1; i < max; i++)
				{
					if (this->getPiece(start.x(), i))//中间有阻隔的棋子
						if (startPiece == 6 || startPiece == -6)//車
							return false;//中间不能有阻隔的棋子
						else if (startPiece == 5 || startPiece == -5)
						{
							count++;
							if (count > 1)return false;//炮中间只能有一个架子
						}
				}
				//炮不能直接吃子，不能空打
				if (startPiece == 5 || startPiece == -5)
					if(count == 0 && endPiece != 0//没有炮架子
						|| count == 1 && endPiece == 0)//不吃子跳跃走棋
						return false;
			}
			else if (start.x() != end.x() && start.y() == end.y())//走横线的情况
			{
				min = start.x() < end.x() ? start.x() : end.x();
				max = start.x() > end.x() ? start.x() : end.x();
				if ((startPiece == 4 || startPiece == -4 ||	//兵卒
					startPiece == 1 || startPiece == -1		//将帅
					)
					&& max - min != 1)//兵卒将帅只能走一步
					return false;
				if (startPiece == 4 && start.y() > 4
					|| startPiece == -4 && start.y() < 5
					)//兵卒过了河才能横走
					return false;
				if ((startPiece == 1 || startPiece == -1)
					&& (end.x() < 3 || end.x() > 5)
					)//将帅不能出中间三条线
					return false;
				for (i = min + 1; i < max; i++)
				{
					if (this->getPiece(i, start.y()))//中间有阻隔的棋子
						if (startPiece == 6 || startPiece == -6)//車
							return false;//中间不能有阻隔的棋子
						else if (startPiece == 5 || startPiece == -5)
						{
							count++;
							if (count > 1)return false;//炮中间只能有一个架子
						}
				}
				//炮不能直接吃子，不能空打
				if (startPiece == 5 || startPiece == -5)
					if (count == 0 && endPiece != 0//没有炮架子
						|| count == 1 && endPiece == 0)//不吃子跳跃走棋
						return false;
			}
		}

		//象
		if (startPiece == 3 || startPiece == -3)
		{
			if (abs(start.x() - end.x()) != 2 || abs(start.y() - end.y()) != 2)//走的不是田
				return false;
			if (startPiece == -3 && end.y() > 4
				|| startPiece == 3 && end.y() < 5
				)//象不能过河
				return false;
			if (this->getPiece((start.x() + end.x()) / 2, (start.y() + end.y()) / 2))//象路线被挡住
				return false;
		}

		//马
		if (startPiece == 7 || startPiece == -7)
		{
			if (
				!(abs(start.x() - end.x()) == 2 && abs(start.y() - end.y()) == 1
					|| abs(start.x() - end.x()) == 1 && abs(start.y() - end.y()) == 2)
				)//马走日
				return false;
			if (abs(start.x() - end.x()) == 2 && this->getPiece((start.x() + end.x()) / 2, start.y())//马横走，马腿被蹩
				|| abs(start.y() - end.y()) == 2 && this->getPiece(start.x(), (start.y() + end.y()) / 2)//马竖走，马腿被蹩
				)
				return false;
		}

		//士
		if (startPiece == 2 || startPiece == -2)
		{
			if (abs(start.x() - end.x()) != 1 || abs(start.y() - end.y()) != 1)//走的不是斜线
				return false;
			if (startPiece == 2 && end.y() < 7
				|| startPiece == -2 && end.y() > 2
				)//士不能越过后三条线
				return false;
			if (end.x() < 3 || end.x() > 5)//士不能出中间三条线
				return false;
		}

		//将帅不能见面
		if (this->masterPos[0].x() == this->masterPos[1].x()//将帅一条线
			&& abs(startPiece) != 1//移动的不是将帅
			&& start.x() == this->masterPos[0].x()//移动的子与将帅一条线
			&& start.y() > this->masterPos[1].y()//移动的子在将帅之间
			&& start.y() < this->masterPos[0].y()//移动的子在将帅之间
			)
		{
			count = 0;
			for (i = this->masterPos[1].y() + 1; i < this->masterPos[0].y(); i++)
			{
				if (this->getPiece(this->masterPos[0].x(), i))//中间有阻隔的棋子
				{
					count++;
				}
			}
			if (count < 2 //将帅之间只有一个棋子
				&& (
					end.x() != start.x() //要被移到其他线路
					|| end.y() < this->masterPos[1].y() //要被移动到将帅之外
					|| end.y() > this->masterPos[0].y()//要被移动到将帅之外
					)
				)
				return false;
		}
		if (startPiece == 1)//移动我方帅
		{
			if (end.x() == this->masterPos[1].x())//移动到的位置，与对方将同一条线
			{
				count = 0;
				for (i = this->masterPos[1].y() + 1; i < end.y(); i++)
				{
					if (this->getPiece(this->masterPos[1].x(), i))//中间有阻隔的棋子
					{
						count++;
					}
				}
				if (count < 1)return false;//移动之后，将帅之间无棋子，故不能移动
			}
			this->masterPos[0] = end;//更新我方帅的位置
		}
		if (startPiece == -1)//移动对方将
		{
			if (end.x() == this->masterPos[0].x())//移动到的位置，与我方帅同一条线
			{
				count = 0;
				for (i = end.y() + 1; i < this->masterPos[0].y(); i++)
				{
					if (this->getPiece(this->masterPos[0].x(), i))//中间有阻隔的棋子
					{
						count++;
					}
				}
				if (count < 1)return false;//移动之后，将帅之间无棋子，故不能移动
			}
			this->masterPos[1] = end;//更新对方将的位置
		}

		//将帅被吃掉
		if (endPiece == 1)
		{
			this->masterPos[0] = QPoint(-1, -1);
		}
		if (endPiece == -1)
		{
			this->masterPos[1] = QPoint(-1, -1);
		}

		//更改棋盘数据
		this->chesspieces[end.x()][end.y()] = this->chesspieces[start.x()][start.y()];
		this->chesspieces[start.x()][start.y()] = 0;
		this->whoseTurn = !this->whoseTurn;
		//返回true
		return true;
		
	}
	return false;
}

