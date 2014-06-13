<?php
/**
 * SQL �桼�ƥ���ƥ����饹 ����
 *
 * static���С��켰�������ϳ�DBMS���饹�ˤ�Ǥ��
 * �ºݤˤ�static����ʤ����ɡ������Ϥ����������ˡ�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('security.inc');

abstract class sql_util {
//public:


// ������ʬ
static public function make_insert($table_name, array $value)
{

  $vname = array();
  $vvalue = array();

  foreach ($value as $key => $val) {
//print $key . "\n";
    $vname[] = $key;
    $vvalue[] =  security::sanitize_db_add_quote($val);
  }

  //
  $sql =  "INSERT INTO " . $table_name . " (" . implode($vname, ",") . ") VALUES (" . implode($vvalue, ",") . ");";

  //
  return $sql;
}

static public function make_update($table_name, array $value, array $where)
{

//print "in to make_update\n";
  $v = array();
  $ret = "";

  //
  foreach ($value as $key => $val) {
    $v[] =  $key . "=" . security::sanitize_db_add_quote($val);
  }

  $sql = "UPDATE " . $table_name . " SET " . implode($v, ",");
  $s = sql_util::make_where($where);
  if ("" != $s) {
    $sql = $sql . " WHERE " . $s;
  }

  //
  $sql = $sql . ";";
  return $sql;
}

static public function make_delete($table_name, array $where)
{

  //
  $sql = "DELETE FROM " . $table_name;
  $s = SQL_UTIL::make_where($where);
  if ("" != $s) {
    $sql = $sql . " WHERE " . $s;
  }

  //
  $sql = $sql . ";";
  return $sql;
}

static public function make_where(array $where)
{

//print "in to make_where\n";
  $w = array();

  foreach ($where as $key => $val) {
    $w[] =  $key . "=" . security::sanitize_db_add_quote($val);
  }
  //
  $s = implode($w, " and ");

//print "out to make_where\n";
  return $s;
}


// ���մط�
/////////////////////

// ǯ�ˤ�륵����
abstract public function eq_year($name, $year);
// ��ˤ�륵����
abstract public function eq_month($name, $month);
// ���ˤ�륵����
abstract public function eq_day($name, $day);
// ���ˤ�륵����
abstract public function eq_hour($name, $hour);
// ʬ�ˤ�륵����
abstract public function eq_min($name, $min);
// �äˤ�륵����
abstract public function eq_sec($name, $sec);
// ���ˤ�륵����
// XXX 0 = ������, 1 = ������, ... 6 = ������
abstract public function eq_week($name, $week_no);


// �ϰϻ���
// (������)���ܤ���(���������)�ޤ�
// 0,1 �ʤ顢��Ƭ���Ԥ��֤�����
abstract public function limited_range($from, $to);


// ���ֻ���
// CALENDER ���֥������Ȼ���
public function term($rec_name, $from_obj, $to_obj)
{
  $ret = 
    '\'' . $from_obj->get_string() . '\' <= ' . $rec_name . ' and ' .
     $rec_name . ' <= \'' . $to_obj->get_string() . '\'';

  //
  return $ret;
}

} // end of class
