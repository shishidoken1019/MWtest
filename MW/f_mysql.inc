<?php
/**
 * DB�ǡ������饹 Mysql
 *
 * SELECT�ˤ�äƵ��äƤ���DB�ǡ������갷���ޤ�
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once("db.inc");

class mysql_data extends db_data {
//public:

  //
  public function __construct($res) {
    //parent::__construct();
    $this->res_ = $res;
  }

  // �ǥ��ȥ饯����mysql_free_result
  public function __destruct() {
    @mysql_free_result($this->res_);
    //parent::__destruct();
  }

  // false�ˤʤä���ǡ���̵��
  public function fetch() {
    if (!($this->row_ = mysql_fetch_row($this->res_))) {
      return false;
    }

    return true;
  }

  // pos�ǥǡ����ΰ��֤����
  public function get_data($pos) {
    return $this->row_[$pos];
  }

  // ���߻��ꤵ��Ƥ룱�ԤΥǡ�������������
  public function get_row() {
    return $this->row_;
  }


//private:
private $res_;
private $row_;
}


/**
 * DB�ϥ�ɥ륯�饹 Mysql
 *
 * DB�ϥ�ɥ���갷���ޤ�
 *
 *
 * @package magicwepon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/
require_once('sql_util_mysql.inc');

class dbh_mysql extends db_handle {
//public:

  public function connect() {
    //
    if (false === (is_null($this->conn_))) {
      return true;
    }
//var_dump($this->conn_);

    // ��������
    $param = "";
    if ("" != $this->get_host_name()) {
      $param = $this->get_host_name();
      if ("" != $this->get_port_num()) {
        $param .= ":" . $this->get_port_num();
      }
    }
//print "mysql param is $param \n";

    // connect
    if (!($this->conn_ = @mysql_connect($param, $this->get_user(), $this->get_pass(), true))) {
//print $this->conn_->mysql_error() . "\n";
      $this->set_error_message("connect error!!");
      return false;
    }
//print "connect\n";
//var_dump($this->conn_);

    // db set
    $ret = mysql_select_db($this->get_database_name(), $this->conn_);
//print 'mysql select db ret is ';
//var_dump($ret);
//print mysql_error();
//print "database is " . $this->get_database_name() . "\n";
//var_dump($this->conn_);

    //
    $this->set_sql_util(new sql_util_mysql);

    //
    return true;
  }

  public function disconnect() {
//print "run disconnect \n";
    return @mysql_close($this->conn_);
  }

  //mysql_data * query(const string& sql);
  public function query($sql) {
//print "mysql $sql \n";
    if (!($result = @mysql_query($sql, $this->conn_))) {
//var_dump($result);
      $this->set_error_message(@mysql_error($this->conn_));
//var_dump($this->get_error_message());
      return null;
    }

    $ret = new mysql_data($result);
    return $ret;
  }

//private:
private $conn_ = null;
}
