<?php

require_once("socket_response_message.inc");		// �����åȤ˴ؤ��������å������򰷤�

/**
 * �����åȤ򰷤����饹
 *
 * XXX ���顼�ϥ�ɥ�Ϥϸ�ۤɼ������Ȥꤢ����ư����Τ�
 *
 * @package magicweapon
 * @access  public
 * @author  Yuuki Ogura <hiruandon2nd@gmail.com>
 * @create  2006/10/13
 * @version $Id$
 **/
class socket {

	/*
	 * ���󥹥ȥ饯��
	 */
	public function __construct() { $this->init(); }

	/*
	 * �����
	 */
	public function init() {
		// XXX �ǥե���ȥץ��ȥ����TCP
		$this->set_tcp();
		// socket_create()�ǻ��ꤹ�륽���åȥ����פ򥻥å�
		$this->set_socket_type();
		// ���ޥ��ȯ�Ԥ����Ǥβ��ԥ����ɤ򥻥å�
		$this->set_crlf();
	}

	/*
	 * TCP�ץ��ȥ�����Ѥ�����
	 * 
	 * XXX ���å�����get_protocol()
	 */
	public function set_tcp() { $this->protocol_ = "tcp"; }

	/*
	 * UDP�ץ��ȥ�����Ѥ�����
	 * 
	 * XXX ���å�����get_protocol()
	 */
	public function set_udp() { $this->protocol_ = "udp"; }

	/*
	 * �ץ��ȥ��륲�å���
	 */
	public function get_protocol() { return $this->protocol_; }

	/*
	 * �ץ��ȥ����ֹ����� 
	 */
	public function get_protocol_num() { return getprotobyname($this->get_protocol()); }

	/*
	 * socket_create�ǻȤ������åȥ����פΥ��å���
	 */
	public function set_socket_type() {

		switch ($this->get_protocol()) {
			case "tcp":
				$this->socket_type_ = SOCK_STREAM;
				break;
			case "udp":
				$this->socket_type_ = SOCK_DGRAM;
				break;
			default:
				$this->socket_type_ = SOCK_STREAM;
		}

	}

	/*
	 * socket_create�ǻȤ������åȥ����פΥ��å���
	 */
	public function get_socket_type() { return $this->socket_type_; }

	/*
	 * ��³��Υݡ����ֹ�򥻥å�
	 */
	public function set_to_port($port) { $this->port_to_ = $port; }

	/*
	 * ��³��Υݡ����ֹ�򥲥å�
	 */
	public function get_to_port() { return $this->port_to_; }

	/*
	 * �����å���³���륵���ӥ�
	 */
	public function set_service($service) {		
		// �����ӥ�̾����ݡ����ֹ�����
		$this->port_to_ = getservbyname($service, $this->get_protocol());
	}

	/*
	 * �����å���³���IP��IP���ɥ쥹ľ����ޤ��ϥɥᥤ��̾�����������ǥ��å�
	 * 
	 * 
	 * @param string ip xxx.xxx.xxx.xxx or domain name 
	 */
	public function set_to_ip_addr($ip) {

		$this->to_ip_ = gethostbyname($ip);
//echo "ip:" . $this->to_ip_ . "\n";
	}

	/*
	 * �����å���³���IP�򥲥å�
	 */
	 public function get_to_ip_addr() { return $this->to_ip_; }
	
	/*
	 * �����å���³
	 */
	public function connect() {

// echo "get_socket_type:" . $this->get_socket_type() . "\n";
// echo "get_protocol_num:" . $this->get_protocol_num() . "\n";
// echo "get_to_ip_addr:" . $this->get_to_ip_addr() . "\n";
// echo "get_to_port:" . $this->get_to_port() . "\n";

		$this->_create();
		$this->_connect();

//var_dump($this->socket_);

	}

	/*
	 * �����åȡ��̿����ν�ü�ˤ��������
	 * XXX �����åȤΥ��å����ϡ�get_socket()
	 */
	private function _create() {

		$this->socket_ = socket_create(AF_INET, $this->get_socket_type(), $this->get_protocol_num());

		if ($this->socket_) {
			return true;
		} else {
// XXX ���顼�ϥ�ɥ�ɤ����롩
			echo "socket_create(): " . socket_strerror($this->socket_) . "\n";
			return false;
		}
	}
	private function get_socket() { return $this->socket_; }

	/*
	 * �����åȾ����³����������
	 */
	private function _connect() {

		if (socket_connect($this->get_socket(), $this->get_to_ip_addr(), $this->get_to_port())) {
			return true;
		} else {
// XXX ���顼�ϥ�ɥ�ɤ����롩
			echo "socket_connect(): " . socket_strerror(socket_last_error()) . "\n";
			return false;
		}
	}

	/*
	 * �����å�����
	 */
	public function disconnect() { socket_close($this->get_socket()); }

	/*
	 * �����åȥǡ����񤭹���
	 */
	public function write($data) {
		socket_write($this->get_socket(), $data);
	}

	/*
	 * �����åȥǡ����ɤ߹���(write�Υ쥹�ݥ�)
	 * XXX $readLength�ν���ͤ�̵����
	 */
	public function read($readLength=2048) {
		// readLength���Τ�1�ѥ��å�ʬ(ñ�ʤ�Хåե�)�Ȳ��ꤷ�ơ�while�ǲ󤹤褦����
		$ret_buf = "";
		while( $buf = socket_read($this->get_socket(), $readLength, PHP_BINARY_READ) ) {
			$ret_buf .= $buf;
		}
		return $ret_buf;
	}

	/*
	 * �����åȥǡ����񤭹��ߡ��ɤ߹���
	 * XXX $readLength�ν���ͤ�̵����
	 */
	public function command($data, $readLength=2048) {

		$this->write($data . $this->get_crlf());	// �����åȥǡ����񤭹���

//print "soc class command is " . $data . "\n";

		$str = $this->read($readLength);					// �����åȤ���write���Ф�����������
		
		// ������å������򰷤����饹
		$res = new socket_response_message();
		$res->set_string($str);

		// ������å�����Ū�˥��顼���ä����㳰���ꤲ��
		if (true == $res->is_error()) {
			throw new Exception($data  . " : " . $res->get_message());
		}

		// XXX ����ϲ���������
		return $res;

	}

	public function set_crlf($d="\r\n") { $this->crlf_ = $d; } 
	private function get_crlf() { return $this->crlf_; }


	private $socket_;			// �����åȥ꥽����
	private $socket_type_;	// �����åȥ�����(SOCK_STREAM,SOCK_DGRAM)
	private $protocol_;		// �ץ��ȥ��� 
	private $to_ip_;				// ��³��IP
	private $service_;			// �����ӥ�̾(http,ssl,ftp etc..)
	private $port_to_;			// ��³��Υݡ����ֹ�

	private $crlf_;				// ���ޥ��ȯ�Ԥ����Ǥβ��ԥ�����

}

/*
// create
$sock_obj_ = new socket();

// ��³���������

// XXX ����ˡŪ��
$sock_obj_->set_service("smtp");

// XXX �̾���Ϥ������顩
//$sock_obj_->set_to_ip_addr("192.168.70.32");
$sock_obj_->set_to_ip_addr("localhost.localdomain");
$sock_obj_->set_to_port(25);

$sock_obj_->connect();

//$sock_obj_->write("HELO");
//echo $sock_obj_->read();

$sock_obj_->write("HELO localhost.localdomain\r\n");
echo $sock_obj_->read();

$sock_obj_->write("MAIL FROM:<y_ogura@quinland.co.jp>\r\n");
echo $sock_obj_->read();

$sock_obj_->write("RCPT TO:<y_ogura@quinland.co.jp>\r\n");
$sock_obj_->write("RCPT TO:<m_takahashi@quinland.co.jp>\r\n");
echo $sock_obj_->read();

$sock_obj_->write("DATA\r\n");
echo $sock_obj_->read();

$sock_obj_->write("from: y_ogura@quinland.co.jp\r\n");
$sock_obj_->write("to: m_takahashi@quinland.co.jp\r\n");
$sock_obj_->write("cc: y_ogura@quinland.co.jp\r\n");
$sock_obj_->write("subject: test\r\n");
$sock_obj_->write("\r\n");
$sock_obj_->write("this is socket send mail test\r\n");
$sock_obj_->write(".\r\n");
$sock_obj_->write("QUIT\r\n");
echo $sock_obj_->read();


$sock_obj_->disconnect();
*/