<?php
/**
 * DBデータクラス PostgreSQL
 *
 * SELECTによって帰ってくるDBデータを取り扱います
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once("db.inc");

class pg_data extends db_data {
//public:

  //
  public function __construct($res) {
    $this->res_ = $res;
    $this->row_int_ = 0;
  }

  // falseになったらデータ無し
  public function fetch() {
    if (!($this->row_ = @pg_fetch_row($this->res_))) {
      return false;
    }

    //
    return true;
  }

  // posでデータの位置を指定
  public function get_data($pos) {
    return $this->row_[$pos];
  }

  // 現在指定されてる１行のデータを全部取得
  public function get_row() {
    return $this->row_;
  }

//private:
private $res_;
private $row_;
}


/**
 * DBハンドルクラス PostgreSQL
 *
 * DBハンドルを取り扱います
 *
 *
 * @package magicwepon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/
require_once("sql_util_postgresql.inc");

class dbh_pgsql extends db_handle {
//public:

  public function connect() {
    // 引数を作る
    $wk = array();
    if ("" != $this->get_host_name()) {
      $buf = "host=" . $this->get_host_name();
      array_push($wk, $buf);
    }
    if ("" != $this->get_port_num()) {
      $buf = "port=" . $this->get_port_num();
      array_push($wk, $buf);
    }
    if ("" != $this->get_database_name()) {
      $buf = "dbname=" . $this->get_database_name();
      array_push($wk, $buf);
    }
    if ("" != $this->get_user()) {
      $buf = "user=" . $this->get_user();
      array_push($wk, $buf);
    }
    if ("" != $this->get_pass()) {
      $buf = "password=" . $this->get_pass();
      array_push($wk, $buf);
    }

    //
    $param = implode(" ", $wk);
//print "param is " . $param . "\n";

    // connect
    if (!($this->conn_ = pg_connect($param))) {
      $this->set_error_message("Connect error!!");
      return false;
    }

    //
    $this->set_sql_util(new sql_util_postgresql);

    //
    return true;
  }

  public function disconnect() {
    @pg_close($this->conn_);
  }

  public function query($sql) {
    if (!($result = @pg_query($this->conn_, $sql))) {
      $this->set_error_message(@pg_last_error($this->conn_));
      return false;
    }

    $ret = new pg_data($result);
    return $ret;
  }

//private:
private $conn_;
}


