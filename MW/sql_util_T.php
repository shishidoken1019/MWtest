<?php

require_once('sql_util.inc');

// �ƥ����Ѥ˥��ߡ����饹

class sql_util_t extends sql_util {
// ǯ�ˤ�륵����
public function eq_year($name, $year){}
// ��ˤ�륵����
public function eq_month($name, $month){}
// ���ˤ�륵����
public function eq_day($name, $day){}
// ���ˤ�륵����
public function eq_hour($name, $hour){}
// ʬ�ˤ�륵����
public function eq_min($name, $min){}
// �äˤ�륵����
public function eq_sec($name, $sec){}
// ���ˤ�륵����
// XXX 0 = ������, 1 = ������, ... 6 = ������
public function eq_week($name, $week_no){}


public function limited_range($from, $to){}

}

$qwk = array();
$where = array();

  $qwk["name1"] = "data1";
  $qwk["name2"] = "da'ta2";
  $qwk["name3"] = "da\\ta3";
  $qwk["name4"] = "40";
  $qwk["name5"] = "50";

  $where["name_key"] = "data_key";
  $where["name_key2"] = "data_key2";

print "insert\n";
print sql_util_t::make_insert("table1", $qwk) . "\n";
print "\nupdate\n";
print sql_util_t::make_update("table1", $qwk, $where) . "\n";
print "\ndelete\n";
print sql_util_t::make_delete("table1", $where) . "\n";



?>
