// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")

#if !defined(AFX_ADOCONN_H__75D447E2_EABB_4A14_9762_DD826E28D19A__INCLUDED_)
#define AFX_ADOCONN_H__75D447E2_EABB_4A14_9762_DD826E28D19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADOConn  
{
// �������
public:
	//���һ��ָ��Connection�����ָ��:
	_ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��:
	_RecordsetPtr m_pRecordset;

// ���巽��
public:
	ADOConn();
	virtual ~ADOConn();
	void OnInitADOConn();							// ��ʼ�����������ݿ�
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);	// ִ�в�ѯ
	BOOL ExecuteSQL(_bstr_t bstrSQL);				// ִ��SQL��䣬Insert Update _variant_t
	void ExitConnect();								// �Ͽ�����
};

#endif // !defined(AFX_ADOCONN_H__75D447E2_EABB_4A14_9762_DD826E28D19A__INCLUDED_)
