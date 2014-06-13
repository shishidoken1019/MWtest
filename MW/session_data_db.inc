<?php

/**
 * ���å��������DB�˽񤭹��९�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

/*
// ͽ�ۤ��Ƥ���ơ��֥����
create table session_data (
        id varchar(64) binary not null,
        data text,
        time datetime,
        PRIMARY KEY (id)
);
*/

require_once("sql_util.inc");
//require_once("security.inc");
require_once("calendar.inc");
require_once("calendar_util.inc");
require_once("session_data.inc");

class session_data_db extends session_data {
//public:

// �������
public function __construct()
{
  //
  parent::__construct();
  // �ơ��֥�̾��Ȥꤢ��������
  $this->tbl_name_ = "session_data";
}

/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @param db_handle $o db_handle���饹(������������饹)�Υ��󥹥���
 */
public function set_db($o) { $this->dbh_ = $o; }
/**
 * DB�ϥ�ɥ�μ���
 *
 * @access public
 * @return db_handle db_handle���饹(������������饹)�Υ��󥹥���
 */
public function get_db() { return $this->dbh_; }


/**
 * �ǡ�����¸�ѥơ��֥�̾������
 *
 * @access public
 * @return string $s �ơ��֥�̾
 */
public function set_tablename($s) { $this->tbl_name_ = $s; }


/**
 * DB�ؤ�session data�ν񤭹���
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function write()
{

  // �ǡ����κ���
  $qwk["data"] = $this->get();
  $qwk["id"] = $this->get_id();
  $qwk["time"] = calendar_util::get_now_string();

  // SQLʸ������
  $sql = sql_util::make_insert($this->tbl_name_, $qwk);

  if (($this->get_db()->query($sql))) {
    return true;
  }
//var_dump($sql);
  // NG�ʤ�UPDATE
  unset ($qwk);
  $qwk["data"] = $this->get();
  $qwk["time"] = calendar_util::get_now_string();
  $where["id"] = $this->get_id();

  //
  $sql = sql_util::make_update($this->tbl_name_, $qwk, $where);
//print $sql . "\n";;
//var_dump($sql);
  if (!($this->get_db()->query($sql))) {
//print "write false\n";
    return false;
  }
  // else
//print "write true\n";
  return true;
}

/**
 * DB����session data�ؤ��ɤ߹���
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function read()
{
  $sql = "SELECT data,time FROM " . $this->tbl_name_ . " WHERE id=" . security::sanitize_db_add_quote($this->get_id()) ;

//print "validity term is " . $this->get_validity_term() . "\n";

  if ($this->get_validity_term() > 0) {
    // ͭ�����¤κ���
    $cal = new calendar;
    $cal->set_now_date();
    $cal->set_epoc($cal->get_epoc() - $this->get_validity_term());

    $sql .= " and time >= '" . $cal->get_string("-") . "'";
  }
  $sql .= ";";
//print $sql . "\n";

  if (!($data = $this->get_db()->query($sql))) {
    return false;
  }
  if (!($data->fetch())) {
    return false;
  }

  //
//var_dump($data->get_data(0));
  $this->set($data->get_data(0));
//var_dump($this);
//print $data->get_data(1) . "\n";
  return true;
}


/**
 * DB��ˤ���session data�κ��
 *
 * �����Υǡ�������������� init�᥽�åɤ�
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function del() {
  $where["id"] = $this->get_id();
  $sql = sql_util::make_delete($this->tbl_name_, $where);
//print $sql . "\n";
  return $this->get_db()->query($sql);
}

/**
 * ���å����ID��¸�ߥ����å�
 *
 * @access public
 * @return boolean ¸�ߤ��Ƥ�����true
 */
public function is_session() {
  $sql = "SELECT count(*) FROM " . $this->tbl_name_ . " WHERE id=" . security::sanitize_db_add_quote($this->get_id()) ;
//print $sql . "\n";

  if (!($data = $this->get_db()->query($sql))) {
//print "is_session NG 1\n";
    return false;
  }
  if (!($data->fetch())) {
//print "is_session NG 2\n";
    return false;
  }

  //
  if ( 0 == $data->get_data(0)) {
//print "is_session NG 3\n";
    return false;
  }

  //
//print "is_session OK\n";
  return true;
}

/**
 * ��񤭤��ʤ��褦�����դ��ʤ����write
 *
 * @access public
 * @return boolean ���꤬�����false��Ʊ�쥻�å����ID̾�ǤΥ쥳���ɤ�����Ȥ���false
 */
public function fix_session()
{
//print "fix Trap 1\n";
  // �Ȥꤢ����is�ǳ�ǧ����
  if (true === $this->is_session()) {
    // ¸�ߤ��Ƥ���NG�äƤ��Ȥ�false�򤫤���
//print "is_session true\n";
    return false;
  }

//print "fix Trap 2\n";
  // INSERT�Ǥ⤦���٥����å�����
  $qwk["data"] = "";
  $qwk["id"] = $this->get_id();
  $qwk["time"] = calendar_util::get_now_string();

  $sql = sql_util::make_insert($this->tbl_name_, $qwk);
//print "$sql \n";

  if (($this->get_db()->query($sql))) {
    // INSERT�Ǥ����Τ�TRUE
    return true;
  }
//print "insert invalid\n";

  // �������äƤ�äݤ��Τ�False
  return false;
}

//private:
private $dbh_; // DB�ϥ�ɥ�
private $tbl_name_;
} // end of class
