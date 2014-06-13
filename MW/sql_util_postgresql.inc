<?php
/**
 * SQL ユーティリティクラス PostgreSQL
 *
 * staticメンバー一式。
 * 実際にはstaticじゃないけど、扱いはそういう風に。
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
// XXX ちと怖いのだが。pg_escape_string使うべきか？
// XXX PostgreSQL 7.2 以降が必要 だが。
/*
// XXX 使うならこんな感じ
public function sanitize_db($base_string)
{
  return pg_escape_string($base_string);
}
*/

// 日付関係
/////////////////////

// 年によるサーチ
public function eq_year($name, $year)
{
  return 'EXTRACT (' . $name . ' FROM year) = ' . $year ;
}

// 月によるサーチ
public function eq_month($name, $month)
{
  return 'EXTRACT (' . $name . ' FROM month) = ' . $month ;
}

// 日によるサーチ
public function eq_day($name, $day)
{
  return 'EXTRACT (' . $name . ' FROM day) = ' . $day ;
}

// 時によるサーチ
public function eq_hour($name, $hour)
{
  return 'EXTRACT (' . $name . ' FROM hour) = ' . $hour ;
}

// 分によるサーチ
public function eq_min($name, $min)
{
  return 'EXTRACT (' . $name . ' FROM minute) = ' . $min ;
}

// 秒によるサーチ
public function eq_sec($name, $sec)
{
  return 'EXTRACT (' . $name . ' FROM second) = ' . $sec ;
}

// 週によるサーチ
// XXX 0 = 日曜日, 1 = 月曜日, ... 6 = 土曜日
public function eq_week($name, $week_no)
{
  return 'EXTRACT (' . $name . ' FROM dow) = ' . $week_no ;
}


// 範囲指定
// (第一引数)行目から(第二引数行)まで
// 0,1 なら、先頭１行を返すこと
public function limited_range($from, $to)
{
  return 'LIMIT ' . $to . ' OFFSET ' . $from;
}

} // end of class

