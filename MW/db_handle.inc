<?php

/**
 * DB�ϥ�ɥ륯�饹
 *
 * DB�ϥ�ɥ�򰷤��ޤ�
 * abstract���饹�ʤΤǡ�ɬ�����������Ƥ�������
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

abstract class db_handle {
//public:

  // ���󥹥ȥ饯���ǽ��������
  public function __construct() {
    // ��ȥ饤�����10���ǥե��ˤ��Ƥ���
    $this->set_connect_retries_num(10);
  }

  // �ǥ��ȥ饯���ǥ��ͥ��������ڤ�
  public  function __destruct() {
    $this->disconnect();
  }

  // ��ȥ饤�դ���connect
  // XXX �ҥ��饹�μ����᥽�åɤ�ʣ����á��
  public function rconnect() {
    // ��ȥ饤����μ���
    $retries_num = $this->get_connect_retries_num();

    // �֤��
    $flg = false;
    while( $retries_num -- ) {
//print "retry is " . $retries_num . "\n";
      if ($this->connect()) {
        $flg = true;
        break;
      }
      // Ŭ����sleep
      // XXX �Ȥꤢ���������
      time_nanosleep(1, mt_rand(0, 500000000) );
    }

    //
    return $flg;
  }

  // ��ȥ饤�����Ϣ
  public function set_connect_retries_num($i)
    { $this->connect_retries_num_ = $i; }
  public function get_connect_retries_num()
    { return $this->connect_retries_num_; }

  // virtual�ؿ��Ƽ�
  abstract public function connect();
  abstract public function disconnect();
  abstract public function query($sql);

  // �ʲ��������Ϣ
  public function set_error_message($s) { $this->err_msg_ = $s; }
  public function get_error_message() { return $this->err_msg_; }

  public function set_user($s) { $this->user_ = $s; }
  public function set_pass($s) { $this->pass_ = $s; }
  public function set_database_name($s) { $this->database_name_ = $s; }
  public function set_host_name($s) { $this->host_name_ = $s; }
  public function set_port_num($s) { $this->port_num_ = $s; }

  public function get_user() { return $this->user_; }
  public function get_pass() { return $this->pass_; }
  public function get_database_name() { return $this->database_name_; }
  public function get_host_name() { return $this->host_name_; }
  public function get_port_num() { return $this->port_num_; }

  //
  public function set_sql_util($o) { $this->sql_util_obj_ = $o; }
  public function get_sql_util() { return $this->sql_util_obj_; }

//private:
private $err_msg_;
private $user_;
private $pass_;
private $database_name_;
private $host_name_;
private $port_num_;
//
private $sql_util_obj_;	// sql_util���󥹥��󥹳�Ǽ�ΰ�

private $connect_retries_num_;	// connect��ȥ饤���
}
