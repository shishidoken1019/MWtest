<?php

// SimpleTest�Ѵ���ե�����

require_once '/opt/www/simpletest/unit_tester.php';
require_once '/opt/www/simpletest/reporter.php';

// �оݤˤʤ륯�饹��include
require_once('multimap.inc');

class simple_test_TT extends UnitTestCase
{
//
public function __construct()
{
  $this->UnitTestCase();
}

// 
public function test()
{
  $obj = new multimap;

  // ��ˣ����֤�find�����å�
  $this->assertNull($obj->find('test'));
  $this->assertIdentical($obj->find_array('test'), array());
  $this->assertIdentical($obj->isempty(), true);
  $this->assertIdentical($obj->size(), 0);
  $obj->clear();

  // �ǡ������ͤù���
  $obj->insert('test-name1', 'test-value1-1');
  $obj->insert('test-name1', 'test-value1-2');
  $obj->insert('test-name1', 'test-value1-3');
  $obj->insert('test-name2', 'test-value2-1');
  $obj->insert('test-name2', 'test-value2-2');
  $obj->insert('test-name3', 'test-value3-1');
  $obj->insert('test', 'test-value');

  //
  $this->assertIdentical($obj->isempty(), false);
  $this->assertIdentical($obj->size(), 7);

  // ���� ���ƥ졼���Ǥ֤�ޤ路
  $names = array();
  $values = array();
  for($itr = $obj->begin(); $itr != $obj->end(); $itr ++) {
    // ʸ�������
    $names[] = $obj->real($itr)->get_first();
    $values[] = $obj->real($itr)->get_second();
  }
//var_dump($names);
//var_dump($values);
  $twk = array_diff($names, array ( "test-name1", "test-name1", "test-name1", "test-name2", "test-name2", "test-name3", "test"));
  $this->assertIdentical($twk, array());

  $twk = array_diff($values, array ( "test-value1-1", "test-value1-2", "test-value1-3", "test-value2-1", "test-value2-2", "test-value3-1", "test-value",));
  $this->assertIdentical($twk, array());

  // key����
  $itrs = $obj->find_array('test-name1');
//var_dump($values);
  $values = array();
  foreach($itrs as $itr) {
    // ʸ�������
    $values[] = $obj->real($itr)->get_second();
  }
//var_dump($values);
  $twk = array_diff($values, array ( "test-value1-1", "test-value1-2", "test-value1-3"));
  $this->assertIdentical($twk, array());


  // ñ��
  $itr = $obj->find('test');
  $this->assertIdentical($obj->real($itr)->get_second(), 'test-value');

  // key����μ���
  $keys = $obj->get_all_keys();
  $twk = array_diff($keys, array ( "test-name1", "test-name2", "test-name3", "test"));
  $this->assertIdentical($twk, array());
//var_dump($keys);

  // key�ͻ�����
  $obj->erase_key('test-name1');
  $ret = $obj->find_array('test-name1');
//var_dump($ret);

/*
  // �������ϥƥ���
  $this->assertIdentical($obj->method(), false);

  // ����ϡ�diff�äƶ��ʤ���ספä�������
  // ������ˡ�Ͻ���Ʊ�ʤΤǰ�����������
  $awk = �оݤˤʤ�����;
  $twk = array_diff($awk, array("value1-1", "value1-2", "value1-3"));
  $this->assertIdentical($twk, array());

  // NULL��
  $this->assertNull($obj->method());
  $this->assertNotNull($obj->method());
*/

}
}

// ��Ư��ʬ���ѹ�����
$test = new simple_test_TT;
$test->run(new TextReporter());

