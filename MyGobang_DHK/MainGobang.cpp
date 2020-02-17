#include "StdAfx.h"
#include "MainGobang.h"


CMainGobang::CMainGobang(void)
{
}


CMainGobang::~CMainGobang(void)
{
	if(pPieces!=NULL)
	{
		delete []pPieces;
		pPieces=NULL;
	}
	if(pmyRectangle!=NULL)
	{
		delete []pmyRectangle;
		pmyRectangle=NULL;
	}
}

//�������̺���
//���ڿ�������̴�С����
//�ؼ�����
void CMainGobang::DrawMainTable(CDC *pDC,CRect rect,int iTableSize)
{
	iSize=iTableSize;
	//�ȸ��Ǳ���
	CRect Back;
	Back.top=rect.top+1;
	Back.bottom=rect.bottom-1;
	Back.left=rect.left+1;
	Back.right=rect.right-1;
	pDC->FillSolidRect(&Back,RGB(240,240,240));//���
	//����ÿ�񳤶�
	idx=(((rect.right-rect.left)/(iTableSize+1))>((rect.bottom-rect.top)/(iTableSize+1)))?
		(rect.bottom-rect.top)/(iTableSize+1):
	    (rect.right-rect.left)/(iTableSize+1);
	CBrush brush(RGB(0,0,0));
	CBrush *OldBrush=pDC->SelectObject(&brush);
	int ixp,iyp;//����������
	//������Ԫ
	ixp=(rect.right-rect.left)/2;
	iyp=(rect.bottom-rect.top)/2;
	pDC->Ellipse(ixp-3,iyp-3,ixp+3,iyp+3);
	//������
	ixp-=4*idx;
	iyp-=4*idx;//���Ͻ�
	pDC->Ellipse(ixp-3,iyp-3,ixp+3,iyp+3);
	iyp+=8*idx;//���½�
	pDC->Ellipse(ixp-3,iyp-3,ixp+3,iyp+3);
	ixp+=8*idx;//���½�
	pDC->Ellipse(ixp-3,iyp-3,ixp+3,iyp+3);
	iyp-=8*idx;//���Ͻ�
	pDC->Ellipse(ixp-3,iyp-3,ixp+3,iyp+3);
	pDC->SelectObject(OldBrush);//�ָ��豸������ԭ���Ļ���
	brush.DeleteObject();//�ͷŻ�ͼ��Դ
	//�������̴�С�������ڴ����м�
	ymin=(rect.bottom-rect.top)/2-(iTableSize-1)/2*idx;
	ymax=ymin+(iTableSize-1)*idx;
	xmin=(rect.right-rect.left)/2-(iTableSize-1)/2*idx;
	xmax=xmin+(iTableSize-1)*idx;
	for(int x=xmin;x<=xmax;x+=idx)
	{
		pDC->MoveTo(x,ymin);
		pDC->LineTo(x,ymax);
	}
	for(int y=ymin;y<=ymax;y+=idx)
	{
		pDC->MoveTo(xmin,y);
		pDC->LineTo(xmax,y);
	}
}

//��κ���
void CMainGobang::SetPieces()
{
	iPiecesNum=iSize*iSize;//�����жϵ�Ԫ��
	iPieces=0;//���Ӽ���
	pPieces=new Pieces[iPiecesNum];//���ɴ洢�����ж�
	for(int i=0;i<iPiecesNum;i++)
	{
		pPieces[i].bIsPieces=false;//Ĭ�ϸ�λ��û������
		if(i%2!=0)
		{
			pPieces[i].bIsBlack=false;//˫��Ϊ������
		}
		else
		{
			pPieces[i].bIsBlack=true;//����Ϊ������
		}
	}
	iRectangleNum=0;
	pmyRectangle=new MyRectangle[2];//����ѡ�п�洢��Ԫ
}

//����ѡ�п�
void CMainGobang::DrawRectangle(CDC *pDC,CPoint pt)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(255,0,0));//��������
	CPen *OldPen=pDC->SelectObject(&pen);
	for(int x=xmin;x<=xmax;x+=idx)
	{
		for(int y=ymin;y<=ymax;y+=idx)
		{
			if((pt.x<=x+0.5*idx)&&(pt.x>x-0.5*idx)&&
				(pt.y<=y+0.5*idx)&&(pt.y>y-0.5*idx)&&
				(NoPieces(x,y))&&(NoRectangle(x,y)))
			{
				//��ѡ�п�
				pDC->MoveTo(x-10,y-5);
				pDC->LineTo(x-10,y-10);
				pDC->LineTo(x-5,y-10);

				pDC->MoveTo(x+10,y-5);
				pDC->LineTo(x+10,y-10);
				pDC->LineTo(x+5,y-10);

				pDC->MoveTo(x-10,y+5);
				pDC->LineTo(x-10,y+10);
				pDC->LineTo(x-5,y+10);

				pDC->MoveTo(x+10,y+5);
				pDC->LineTo(x+10,y+10);
				pDC->LineTo(x+5,y+10);
				//��ֵ
				pmyRectangle[iRectangleNum].x=x;
				pmyRectangle[iRectangleNum].y=y;
				iRectangleNum++;
			}
		}
	}
	if(iRectangleNum==2)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(240,240,240));//��������
		CPen *OldPen=pDC->SelectObject(&pen);
		int x,y;
		x=pmyRectangle[0].x;
		y=pmyRectangle[0].y;
		//���ѡ�п�
		pDC->MoveTo(x-10,y-5);
		pDC->LineTo(x-10,y-10);
		pDC->LineTo(x-5,y-10);

		pDC->MoveTo(x+10,y-5);
		pDC->LineTo(x+10,y-10);
		pDC->LineTo(x+5,y-10);

		pDC->MoveTo(x-10,y+5);
		pDC->LineTo(x-10,y+10);
		pDC->LineTo(x-5,y+10);

		pDC->MoveTo(x+10,y+5);
		pDC->LineTo(x+10,y+10);
		pDC->LineTo(x+5,y+10);
		//���ø�ֵ
		pmyRectangle[0].x=pmyRectangle[1].x;
		pmyRectangle[0].y=pmyRectangle[1].y;
		iRectangleNum=1;//���ü���
	}
	pDC->SelectObject(OldPen);//�ָ��豸������ԭ���Ļ���
	pen.DeleteObject();//�ͷŻ�ͼ��Դ
}

//�������Ӻ���
void CMainGobang::DrawPieces(CDC *pDC,CRect rect,CPoint pt)
{
	pt.x-=rect.left;//ת��Ϊ�ؼ�������
	pt.y-=rect.top;
	int iTmp;
	if(pPieces[iPieces].bIsBlack==true)//������
	{
		iTmp=0;
	}
	if(pPieces[iPieces].bIsBlack==false)//������
	{
		iTmp=255;
	}
	for(int x=xmin;x<=xmax;x+=idx)
	{
		for(int y=ymin;y<=ymax;y+=idx)
		{
			if((pt.x<=x+0.5*idx)&&(pt.x>x-0.5*idx)&&
				(pt.y<=y+0.5*idx)&&(pt.y>y-0.5*idx)&&
				(NoPieces(x,y)))
			{	
				//������
				CBrush brush(RGB(iTmp,iTmp,iTmp));
	            CBrush *OldBrush=pDC->SelectObject(&brush);
				pDC->Ellipse(x-10,y-10,x+10,y+10);
				pDC->SelectObject(OldBrush);//�ָ��豸������ԭ���Ļ���
	            brush.DeleteObject();//�ͷŻ�ͼ��Դ
				//������
				CPen penClearMark;//���������ǵĻ���
				penClearMark.CreatePen(PS_SOLID,1,RGB(abs(iTmp-255),abs(iTmp-255),abs(iTmp-255)));
				CPen *OldPenClearMark=pDC->SelectObject(&penClearMark);
				pDC->MoveTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y-3);
				pDC->LineTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y+4);
				pDC->MoveTo(pPieces[iPieces-1].x-3,pPieces[iPieces-1].y);
				pDC->LineTo(pPieces[iPieces-1].x+4,pPieces[iPieces-1].y);
				pDC->SelectObject(OldPenClearMark);//�ָ��豸������ԭ���Ļ���
	            penClearMark.DeleteObject();//�ͷŻ�ͼ��Դ
				//�����
				CPen penMark;//���ڻ��Ʊ�ǵĻ���
				penMark.CreatePen(PS_SOLID,1,RGB(255,0,0));
				CPen *OldPenMark=pDC->SelectObject(&penMark);
				pDC->MoveTo(x,y-3);
				pDC->LineTo(x,y+4);//�ֲ�����̫С���µĲ��Գ�
				pDC->MoveTo(x-3,y);
				pDC->LineTo(x+4,y);
				pDC->SelectObject(OldPenMark);//�ָ��豸������ԭ���Ļ���
				penMark.DeleteObject();//�ͷŻ�ͼ��Դ
				//��ֵ
				pPieces[iPieces].bIsPieces=true;
				pPieces[iPieces].x=x;
				pPieces[iPieces].y=y;
				//������1
				iPieces++;
			}
		}
	}
}

//������Ӻ���/���ڻ���
////////////////////////////////////////////////////problem:�������˫��������һ��ֻ�ܻ�һ�� ӦΪ�������ܻ�һ��
bool CMainGobang::ClearPieces(CDC *pDC,bool &bBlack)
{
	CRect rect;
	if(pPieces[0].bIsPieces)
	{
		rect.bottom=pPieces[iPieces-1].y+10;
		rect.top=pPieces[iPieces-1].y-10;
		rect.left=pPieces[iPieces-1].x-10;
		rect.right=pPieces[iPieces-1].x+10;
		pDC->FillSolidRect(&rect,RGB(240,240,240));//���
	
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		CPen *OldPen=pDC->SelectObject(&pen);
		pDC->MoveTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y-10);
		pDC->LineTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y+10);
		pDC->MoveTo(pPieces[iPieces-1].x-10,pPieces[iPieces-1].y);
		pDC->LineTo(pPieces[iPieces-1].x+10,pPieces[iPieces-1].y);
		pDC->SelectObject(OldPen);//�ָ��豸������ԭ���Ļ���
		pen.DeleteObject();//�ͷŻ�ͼ��Դ

		pPieces[iPieces-1].x=NULL;
		pPieces[iPieces-1].y=NULL;
		pPieces[iPieces-1].bIsPieces=false;
		if((iPieces-1)%2==0)
		{
			bBlack=false;
		}
		else
		{
			bBlack=true;
		}
		iPieces--;//������1
		return true;
	}
	else
	{
		return false;
	}
}

//ѭ���������� //���Խ��ˢ������
void CMainGobang::KeepPieces(CDC *pDC,CRect rect,int iTableSize)
{
	ymin=(rect.bottom-rect.top)/2-(iTableSize-1)/2*idx;
	ymax=ymin+(iTableSize-1)*idx;
	xmin=(rect.right-rect.left)/2-(iTableSize-1)/2*idx;
	xmax=xmin+(iTableSize-1)*idx;
	int iTmp;
	for(int i=0;i<iPieces;i++)
	{
		if(!NoPieces(pPieces[i].x,pPieces[i].y))
		{
			if(i%2==0)//������
			{
				iTmp=0;
			}
			else//������
			{
				iTmp=255;
			}
			//������
			CBrush brush(RGB(iTmp,iTmp,iTmp));
			CBrush *OldBrush=pDC->SelectObject(&brush);
			pDC->Ellipse(pPieces[i].x-10,pPieces[i].y-10,pPieces[i].x+10,pPieces[i].y+10);
			pDC->SelectObject(OldBrush);//�ָ��豸������ԭ���Ļ���
			brush.DeleteObject();//�ͷŻ�ͼ��Դ
			//�����
			CPen penMark;//���ڻ��Ʊ�ǵĻ���
			penMark.CreatePen(PS_SOLID,1,RGB(255,0,0));
			CPen *OldPenMark=pDC->SelectObject(&penMark);
			pDC->MoveTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y-3);
			pDC->LineTo(pPieces[iPieces-1].x,pPieces[iPieces-1].y+4);//�ֲ�����̫С���µĲ��Գ�
			pDC->MoveTo(pPieces[iPieces-1].x-3,pPieces[iPieces-1].y);
			pDC->LineTo(pPieces[iPieces-1].x+4,pPieces[iPieces-1].y);
			pDC->SelectObject(OldPenMark);//�ָ��豸������ԭ���Ļ���
			penMark.DeleteObject();//�ͷŻ�ͼ��Դ
		}
	}
}

//�жϸ�λ�����Ƿ���ѡ�п�
bool CMainGobang::NoRectangle(int x,int y)
{
	bool bNoRectangle;
	bNoRectangle=true;
	for(int i=0;i<2;i++)
	{
		if((x==pmyRectangle[i].x)&&(y==pmyRectangle[i].y))
		{
			bNoRectangle=false;
		}
	}
	return bNoRectangle;
}

//�жϸ�λ�����Ƿ�������
bool CMainGobang::NoPieces(int x,int y)
{
	for(int i=0;i<iPiecesNum;i++)
	{
		if((x==pPieces[i].x)&&(y==pPieces[i].y)&&(pPieces[i].bIsPieces==false))
		{
			return true;
		}
		if((x==pPieces[i].x)&&(y==pPieces[i].y)&&(pPieces[i].bIsPieces==true))
		{
			return false;
		}
	}
}

//�жϸ�λ����������ɫ
bool CMainGobang::IsBlack(int x,int y)
{
	for(int i=0;i<iPiecesNum;i++)
	{
		if((x==pPieces[i].x)&&(y==pPieces[i].y)&&(pPieces[i].bIsBlack==false))
		{
			return false;
		}
		if((x==pPieces[i].x)&&(y==pPieces[i].y)&&(pPieces[i].bIsBlack==true))
		{
			return true;
		}
	}
}

//��������������
//up1,down2,left3,right4,up-left5,down-right6,up-right7,down-left8
bool CMainGobang::IsConnect(int iDir,int x,int y)
{
	bool bIsConnect=false;
	if(((iDir==1)&&(IsBlack(x,y)==IsBlack(x,y-idx))&&(!NoPieces(x,y-idx)))//���ϲ���
		||((iDir==2)&&(IsBlack(x,y)==IsBlack(x,y+idx))&&(!NoPieces(x,y+idx)))//���²���
		||((iDir==3)&&(IsBlack(x,y)==IsBlack(x-idx,y))&&(!NoPieces(x-idx,y)))//�������
		||((iDir==4)&&(IsBlack(x,y)==IsBlack(x+idx,y))&&(!NoPieces(x+idx,y)))//���Ҳ���
		||((iDir==5)&&(IsBlack(x,y)==IsBlack(x-idx,y-idx))&&(!NoPieces(x-idx,y-idx)))//�����ϲ���
		||((iDir==6)&&(IsBlack(x,y)==IsBlack(x+idx,y+idx))&&(!NoPieces(x+idx,y+idx)))//�����²���
		||((iDir==7)&&(IsBlack(x,y)==IsBlack(x+idx,y-idx))&&(!NoPieces(x+idx,y-idx)))//�����ϲ���
		||((iDir==8)&&(IsBlack(x,y)==IsBlack(x-idx,y+idx))&&(!NoPieces(x-idx,y+idx))))//�����²���
	{
		bIsConnect=true;
	}
	return bIsConnect;
}

//�����������Ӹ���
int CMainGobang::ConnectNum()
{
	int iConnect;//����������
	int iGetNum;//����������
	int icx,icy;//����λ�ƿ�����
	int iTmp;//�м����
	//���᷽��***************
	iGetNum=iConnect=1;
	icy=0;
	while(iGetNum<5)//���ϲ���5��
	{
		if(IsConnect(1,pPieces[iPieces-1].x,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum=1;
	icy=0;
	while(iGetNum<5)//�����²���
	{
		if(IsConnect(2,pPieces[iPieces-1].x,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp=iConnect;
	//���᷽��****************
	iGetNum=iConnect=1;
	icx=0;
	while(iGetNum<5)
	{
		if(IsConnect(3,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y))
		{
			iConnect++;
			icx--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum=1;
	icx=0;
	while(iGetNum<5)
	{
		if(IsConnect(4,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y))
		{
			iConnect++;
			icx++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp=max(iTmp,iConnect);
	//����-���·���****************
	iGetNum=iConnect=1;
	icx=icy=0;
	while(iGetNum<5)
	{
		if(IsConnect(5,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icx--;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum=1;
	icx=icy=0;
	while(iGetNum<5)
	{
		if(IsConnect(6,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icx++;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp=max(iTmp,iConnect);
	//����-���·���****************
	iGetNum=iConnect=1;
	icx=icy=0;
	while(iGetNum<5)
	{
		if(IsConnect(7,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icx++;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum=1;
	icx=icy=0;
	while(iGetNum<5)
	{
		if(IsConnect(8,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
		{
			iConnect++;
			icx--;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iConnect=max(iTmp,iConnect);
	return iConnect;
}

//�������������Ӹ���
//void CMainGobang::MaConnectNum(int iConnectNum,int iDir)
//{
//	int iGetNum;//����������
//	int icx,icy;//����λ�ƿ�����
//	int iTmp;//�м����
//	//////////////////////////////���ϲ���////////////////////////////////
//	iGetNum=iConnectNum=1;
//	iDir=1;
//	icy=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(iDir,pPieces[iPieces-1].x,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icy--;
//		iGetNum++;
//	}
//	//////////////////////////////���²���////////////////////////////////
//	iGetNum=1;
//	icy=0;
//	while(iGetNum<5)//�����²���
//	{
//		if(IsConnect(2,pPieces[iPieces-1].x,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icy++;
//		iGetNum++;
//	}
//	iTmp=iConnectNum;
//	//���᷽��****************
//	iGetNum=iConnectNum=1;
//	icx=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(3,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y))
//		{
//			iConnectNum++;
//		}
//		icx--;
//		iGetNum++;
//	}
//	iGetNum=1;
//	icx=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(4,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y))
//		{
//			iConnectNum++;
//		}
//		icx++;
//		iGetNum++;
//	}
//	iTmp=max(iTmp,iConnectNum);
//	//����-���·���****************
//	iGetNum=iConnectNum=1;
//	icx=icy=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(5,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icx--;
//		icy--;
//		iGetNum++;
//	}
//	iGetNum=1;
//	icx=icy=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(6,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icx++;
//		icy++;
//		iGetNum++;
//	}
//	iTmp=max(iTmp,iConnectNum);
//	//����-���·���****************
//	iGetNum=iConnectNum=1;
//	icx=icy=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(7,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icx++;
//		icy--;
//		iGetNum++;
//	}
//	iGetNum=1;
//	icx=icy=0;
//	while(iGetNum<5)
//	{
//		if(IsConnect(8,pPieces[iPieces-1].x+icx*idx,pPieces[iPieces-1].y+icy*idx))
//		{
//			iConnectNum++;
//		}
//		icx--;
//		icy++;
//		iGetNum++;
//	}
//	iConnectNum=max(iTmp,iConnectNum);
//}

//�����������ӷ���
int CMainGobang::ConnectDir()
{
	int iDir;
	for(iDir=1;iDir<9;iDir++)
	{
		if(IsConnect(iDir,pPieces[iPieces-1].x,pPieces[iPieces-1].y))
		{
			return iDir;
		}
	}
}

//�������庯��
void CMainGobang::MachineDraw(CDC *pDC)
{
	int x,y;
	///////////First Machine Pieces////////////////////////////////
	if(iPieces==1)
	{
		//Always in top
		x=pPieces[iPieces-1].x+idx;
		y=pPieces[iPieces-1].y;
		pDC->Ellipse(x-10,y-10,x+10,y+10);
		//��ֵ
		pPieces[iPieces].bIsPieces=true;
		pPieces[iPieces].x=x;
		pPieces[iPieces].y=y;
		//������1
		iPieces++;
	}
	////////////////////////////////////////////////
	///////////Defence Part
	///////////////////////////////////////////////
	if(ConnectNum()==2)
	{
		if(ConnectDir()==1)
		{
			x=pPieces[iPieces-1].x;
			y=abs(pPieces[iPieces-1].y+idx-pPieces[iPieces-2].y)<abs(pPieces[iPieces-1].y-2*idx-pPieces[iPieces-2].y)?
				pPieces[iPieces-1].y+idx:pPieces[iPieces-1].y-2*idx;
			pDC->Ellipse(x-10,y-10,x+10,y+10);
			//��ֵ
			pPieces[iPieces].bIsPieces=true;
			pPieces[iPieces].x=x;
			pPieces[iPieces].y=y;
			//������1
			iPieces++;
		}
		if(ConnectDir()==2)
		{
			x=pPieces[iPieces-1].x;
			y=abs(pPieces[iPieces-1].y+2*idx-pPieces[iPieces-2].y)<abs(pPieces[iPieces-1].y-idx-pPieces[iPieces-2].y)?
				pPieces[iPieces-1].y+2*idx:pPieces[iPieces-1].y-idx;
			pDC->Ellipse(x-10,y-10,x+10,y+10);
			//��ֵ
			pPieces[iPieces].bIsPieces=true;
			pPieces[iPieces].x=x;
			pPieces[iPieces].y=y;
			//������1
			iPieces++;
		}
	}
	///////////////////////////////////////
	//����ģ��
	///////////////////////////////////////

}

//�ж��Ƿ�ʤ��
bool CMainGobang::Success()
{
	bool bSuccess;
	bSuccess=false;
	if(ConnectNum()>=5)
	{
		if(pPieces[iPieces-1].bIsBlack)
		{
			AfxMessageBox(_T("����ʤ��!"));
		}
		if(!pPieces[iPieces-1].bIsBlack)
		{
			AfxMessageBox(_T("����ʤ��!"));
		}
		bSuccess=true;
	}
	return bSuccess;
}

//���̱�Ǻ���
void CMainGobang::ReplayMark(CDC *pDC)
{
	CString strNum;//���ֱ��
	//�趨����
	CFont m_newFont;//������������ַ���������
	CFont *m_OldFont;//���ڻ�ԭԭ��������
	m_newFont.CreatePointFont(80,_T("����"));//�������壬8*n�����ظߵ�����
	m_OldFont = (CFont*)pDC->SelectObject(&m_newFont);//�����帳���豸������
	pDC->SetBkMode(TRANSPARENT);//�����������ı���͸��
	//�������ֵ����ͼ�ؼ�
	for(int i=0;i<iPieces;i++)
	{
		strNum.Format(_T("%d"),i+1);
		if(i%2==0)
		{
			pDC->SetTextColor(RGB(255,255,255));//����������ɫ
		}
		else
		{
			pDC->SetTextColor(RGB(0,0,0));//����������ɫ
		}
		pDC->TextOut(pPieces[i].x-5,pPieces[i].y-5,strNum);
	}
	pDC->SelectObject(m_OldFont);//�ָ�ԭ����
	if(pPieces!=NULL)
	{
		delete []pPieces;
		pPieces=NULL;
	}
}