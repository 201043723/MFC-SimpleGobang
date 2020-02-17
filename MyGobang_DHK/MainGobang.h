#pragma once
struct Pieces//�����жϵ�Ԫ
{
	bool bIsPieces;//�Ƿ�������
	bool bIsBlack;//��������
	int x,y;//�������ڸ�
};

struct MyRectangle
{
	int x,y;//ѡ�п��������
};

//�������㷨����
class CMainGobang
{
public:
	CMainGobang(void);
	~CMainGobang(void);
private:
	/////basic information
	int iSize;//���̴�С����
	int xmax,xmin,ymax,ymin;//���̴�С����
	int idx;//����ÿС�񳤶�
	/////pieces information
	int iPieces;//���Ӽ���//��ǰ���Ӽ���ΪiPieces-1
	int iPiecesNum;//��������
	Pieces *pPieces;//����
	/////rectangle information
	int iRectangleNum;//ѡ�п����
	MyRectangle *pmyRectangle;//ѡ�п�
	/////for draw rectangle&draw pieces
	bool NoRectangle(int x,int y);//�жϸ�λ�����Ƿ���ѡ�п�
	bool NoPieces(int x,int y);//�жϸ�λ�����Ƿ�������
	/////for judge win
	bool IsBlack(int x,int y);//�жϸ�λ����������ɫ
	bool IsConnect(int iDir,int x,int y);//��������������
	int ConnectNum();//�����������Ӹ���
	/////for machine fight
	//void MaConnectNum(int iConnectNum,int iDir);//�������������Ӹ���/iDir�������
	int ConnectDir();//�����������ӷ���
public:
	void DrawMainTable(CDC *pDC,CRect rect,int iTableSize);//�������̺���
	void SetPieces();//��κ���//����ʼ��������������̴���ֿ�
	void DrawRectangle(CDC *pDC,CPoint pt);//����ѡ�п�/�����Ƿ����
	void DrawPieces(CDC *pDC,CRect rect,CPoint pt);//�������Ӻ���
	bool ClearPieces(CDC *pDC,bool &bBlack);//������Ӻ���/���ڻ���
	void KeepPieces(CDC *pDC,CRect rect,int iTableSize);//ѭ���������� //���Խ��ˢ������
	void MachineDraw(CDC *pDC);//�������庯��

	bool Success();//�ж�ʤ������
	void ReplayMark(CDC *pDC);//���̱�Ǻ���
};

