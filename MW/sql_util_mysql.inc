<?php
/**
 * SQL �桼�ƥ���ƥ����饹 MySQL
 *
 * static���С��켰��
 * �ºݤˤ�static����ʤ����ɡ������Ϥ����������ˡ�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/
require_once('sql_util.inc');

class sql_util_mysql extends sql_util {
//public:

//public function sanitize_db($base_string)
// XXX �����ݤ��Τ�����mysql_escape_string�Ȥ��٤�����
/*
// XXX �Ȥ��ʤ餳��ʴ���
public function sanitize_db($base_string)
{
  return mysql_escape_string($base_string);
  return mysql_real_escape_string($base_string);
}
*/

// ���մط�
/////////////////////

// ǯ�ˤ�륵����
public function eq_year($name, $year)
{
  return 'YEAR(' . $name . ') = ' . $year;
}

// ��ˤ�륵����
public function eq_month($name, $month)
{
  return 'MONTH(' . $name . ') = ' . $month;
}

// ���ˤ�륵����
public function eq_day($name, $day)
{
  return 'DAYOFMONTH(' . $name . ') = ' . $day;
}

// ���ˤ�륵����
public function eq_hour($name, $hour)
{
  return 'HOUR(' . $name . ') = ' . $hour;
}

// ʬ�ˤ�륵����
public function eq_min($name, $min)
{
  return 'MINUTE(' . $name . ') = ' . $min;
}

// �äˤ�륵����
public function eq_sec($name, $sec)
{
  return 'SECOND(' . $name . ') = ' . $sec;
}

// ���ˤ�륵����
// XXX 0 = ������, 1 = ������, ... 6 = ������
public function eq_week($name, $week_no)
{
  // MySQL�ϣ��������ȤʤΤǡ����󥯥����
  $week_no ++;
  return 'DAYOFWEEK(' . $name . ') = ' . $week_no;
}


// �ϰϻ���
// (������)���ܤ���(���������)�ޤ�
// 0,1 �ʤ顢��Ƭ���Ԥ��֤�����
public function limited_range($from, $to)
{
  return 'LIMIT ' . $from . ',' . $to;
}

} // end of class
