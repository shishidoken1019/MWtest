<?php
/**
 * SQL �桼�ƥ���ƥ����饹 PostgreSQL
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

class sql_util_postgresql extends sql_util {
//public:

//public function sanitize_db($base_string)
// XXX �����ݤ��Τ�����pg_escape_string�Ȥ��٤�����
// XXX PostgreSQL 7.2 �ʹߤ�ɬ�� ������
/*
// XXX �Ȥ��ʤ餳��ʴ���
public function sanitize_db($base_string)
{
  return pg_escape_string($base_string);
}
*/

// ���մط�
/////////////////////

// ǯ�ˤ�륵����
public function eq_year($name, $year)
{
  return 'EXTRACT (' . $name . ' FROM year) = ' . $year ;
}

// ��ˤ�륵����
public function eq_month($name, $month)
{
  return 'EXTRACT (' . $name . ' FROM month) = ' . $month ;
}

// ���ˤ�륵����
public function eq_day($name, $day)
{
  return 'EXTRACT (' . $name . ' FROM day) = ' . $day ;
}

// ���ˤ�륵����
public function eq_hour($name, $hour)
{
  return 'EXTRACT (' . $name . ' FROM hour) = ' . $hour ;
}

// ʬ�ˤ�륵����
public function eq_min($name, $min)
{
  return 'EXTRACT (' . $name . ' FROM minute) = ' . $min ;
}

// �äˤ�륵����
public function eq_sec($name, $sec)
{
  return 'EXTRACT (' . $name . ' FROM second) = ' . $sec ;
}

// ���ˤ�륵����
// XXX 0 = ������, 1 = ������, ... 6 = ������
public function eq_week($name, $week_no)
{
  return 'EXTRACT (' . $name . ' FROM dow) = ' . $week_no ;
}


// �ϰϻ���
// (������)���ܤ���(���������)�ޤ�
// 0,1 �ʤ顢��Ƭ���Ԥ��֤�����
public function limited_range($from, $to)
{
  return 'LIMIT ' . $to . ' OFFSET ' . $from;
}

} // end of class
