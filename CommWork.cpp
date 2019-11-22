#include "stdafx.h"
#include "DataType.h"
#include "CommWork.h"
#include "SystemMemory.h"

CCommWork::CCommWork(std::string name)
	:CWorkBase(name)
{
	memset(&_target, 0, sizeof(ControlData_t));
	memset(&_current, 0, sizeof(ControlData_t));

	_memname_tar = name + "_Controller_Target";
	_memname_cur = name + "_Controller_Current";
	CREATE_SYSTEM_MEMORY(_memname_tar, ControlData_t);
	CREATE_SYSTEM_MEMORY(_memname_cur, ControlData_t);
	CREATE_SYSTEM_MEMORY("MyMotorCurrentData", ControlData_t);

	_sendPacket.data.header[0] = _sendPacket.data.header[1] = _sendPacket.data.header[2] = _sendPacket.data.header[3] = 0xFF;
	_sendPacket.data.id = 1;
	_sendPacket.data.mode = 2;
	_sendPacket.data.size = sizeof(Packet_t);

}


CCommWork::~CCommWork() {

	DELETE_SYSTEM_MEMORY(_memname_tar);
	DELETE_SYSTEM_MEMORY(_memname_cur);
	DELETE_SYSTEM_MEMORY("MyMotorCurrentData");
	ClosePort();
}



bool CCommWork::OpenPort(std::string name, int baudRate) {

	return _comm.Open(name.c_str(), baudRate);
}



void CCommWork::ClosePort() {

	_comm.Close();
}


//�� �Լ��� ���� ����Ǵ��� �˾ƾ���
void CCommWork::_execute() {

	/*DataType_t ode_data;

	GET_SYSTEM_MEMORY("JointData", ode_data);*/

	GET_SYSTEM_MEMORY(_memname_tar, _target);

	static int mode, readSize = 0, checkSize;
	static unsigned char check;

	if (_comm.isOpen()) {

		//_target�� MFC���� ���� ���� ���ΰ� �³�??
		//MFC���� ������ ������ _sendPacket���ٰ� ��� �����ε��ϴ�.
		_sendPacket.data.check = 0;
		_sendPacket.data.pos = _target.position * 1000;
		_sendPacket.data.velo = _target.velocity * 1000;
		_sendPacket.data.cur = _target.current * 1000;


		//checkSum
		//���⼭ checksum ����ϰ��� packet�� �ִ°����� �� �����ִ°���?
		for (int i = 8; i < sizeof(Packet_t); i++)
			_sendPacket.data.check += _sendPacket.buffer[i];

		//��Ŷ ����
		_comm.Write((char*)_sendPacket.buffer, sizeof(Packet_t));

		//128���� ���� ��Ŷ �ٷ� �б�
		readSize = _comm.Read((char*)_recvBuf, 4096);
		//printf("Read : %d\n", readSize);

		//_recvBuf�� 4096¥�� �迭
		for (int i = 0; i < readSize; i++) {

			switch (mode) {

			case STATE_WAIT:
				if (_recvBuf[i] == 0xFF) {
					checkSize++;
					if (checkSize == 4) {
						mode = STATE_CHECK_ID;
					}
				}
				else {
					checkSize = 0;
				}
				break;

			//ID, size, mode, check�� ����
			case STATE_CHECK_ID:

				//_recvBuf�� ID�� ODE�� ���𰡿� ��ġ�ϴ��� Ȯ���ϴ� �κ��� ���µ�
				_packet.buffer[checkSize++] = _recvBuf[i];

				if (checkSize == 8) {
					mode = STATE_GET_DATA;
				}
				break;

			//data �޴ºκ� (pos, vel, cur)
			case STATE_GET_DATA:

				_packet.buffer[checkSize++] = _recvBuf[i];

				// _packet.data.size ���� ������ �ȵǾ��־�
				if (checkSize == _packet.data.size) {

					printf("pos : %d, velo : %d, cur : %d\n",
						_packet.data.pos,
						_packet.data.velo,
						_packet.data.cur);

					_current.position = _packet.data.pos / 1000.;
					_current.velocity = _packet.data.velo;
					_current.current = _packet.data.cur;

					//memset(_recvBuf, 0, readSize);
					mode = 0;
					checkSize = 0;
				}

			}
		}

	}

	//�ٸ������� �̰Ÿ� �����ٰ� �����
	SET_SYSTEM_MEMORY(_memname_cur, _current);
	SET_SYSTEM_MEMORY("MyMotorCurrentData", _current);
}
