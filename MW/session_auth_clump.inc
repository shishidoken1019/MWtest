<?php

/**
 * ���å������auth�ơ��֥륢��������clump���饹
 *
 * �ѥ���ɡ��Ƽ����¤����äƤ���ơ��֥�ؤ�clump
 * ����Ū�ʥơ��֥륤�᡼���ϰʲ��ΤȤ���
create table auth_user (
   id  ���饤�����ID
   pass
   status(���ơ�����
     0:����  1:���å�(���å�����ӥ�����å��ϥ��ץ�Ǥ������)
     2�ʹ�:��Class�����
   lock_time unsigned long
     (������å�����������٤�����:time_t��(time()�ؿ��Ǽ����Ǥ�����)��)
     �̾�ϣ������ʳ��λ��ˤϰ�����å�����Ƥ�����֤Ȥʤ�
   err_count // ���顼�������
);

create table auth_user (
   id varchar(64) not null,
   pass  varchar(64) not null,
   status  varchar(8),
   lock_time bigint,
   err_count bigint,
   PRIMARY KEY (id)
);

 * �Ĥ��ǡ�sha-1�ǥѥ����'pass'�ξ���insertʸ
insert into auth_user(id, pass, status, lock_time, err_count) value ( 'id', '9d4e1e23bd5b727046a9e3b4b7db57bd8d6ee684', 0, 0, 0);

 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once("data_clump.inc");

class session_auth_clump extends data_clump {

public function __construct()
{
  //
  //$this->init();
  parent::__construct();
}

//
public function init()
{
  parent::init();
  $this->set_element();	// �桼����Ͽ���̤����Ǥ���Ͽ
}

/**
 * ����Ū�ʾ��������
 *
 * �ơ��֥�̾����ӥ����̾�����ꤹ��
 *
 * @access protected
 * @return boolean false�ϸ������곰��
 */
protected function set_element()
{
 //
 $this->set_table_name("auth_user");

 // $inname, $cginame, $tmpname, $dbname, $keyflg
 $this->push_element("id", "", "", "", "pk");
 $this->push_element("pass", "", "", "", "");
 $this->push_element("status", "", "", "", "");
 $this->push_element("lock_time", "", "", "", "");
 $this->push_element("err_count", "", "", "", "");
}


//private:


} // end of class
