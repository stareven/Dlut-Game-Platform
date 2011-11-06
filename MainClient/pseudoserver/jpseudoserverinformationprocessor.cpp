#include "jpseudoserverinformationprocessor.h"

#include <Global/CodeError>
#include <Socket/JServerSocketBase>
#include <Information/JInformation>
#include <ClientRequest/JInformationRequestByHeadBase>

using namespace NetworkData;

JPseudoServerInformationProcessor::JPseudoServerInformationProcessor(JServerSocketBase *socket) :
	JServerInformationProcessorBase(socket->getSession(),socket)
{
}

void JPseudoServerInformationProcessor::processDownloadRemoteMtime(const JHead& head)
{
	JTime_t remoteMtime=0;
	JInformationRequestByHeadBase req;
	req.rqsRemoteMtime(head);
	if(req.waitForRemoteMtime(head,1000)){
		remoteMtime=req.getRemoteMtime(head);
	}
	replyMtime(head,remoteMtime);
}

void JPseudoServerInformationProcessor::processDownloadData(const JHead& head)
{
	JInformationRequestByHeadBase req;
	JTime_t localMtime=req.getLastLocalMtime();
	QByteArray data;
	req.rqsInformationData(head);
	if(req.waitForInformationData(head,1000)){
		localMtime=req.getLocalMtime(head);
		data = req.getInformationData(head);
	}

}

void JPseudoServerInformationProcessor::processUploadData(const JHead& head,const QByteArray&)
{
	replyUploadResult(head,EPermissionDenied);
}
