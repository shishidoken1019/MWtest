<?php

// XXX
require_once('/opt/www/mw.conf');

//
require_once '/opt/www/simpletest/unit_tester.php';
require_once '/opt/www/simpletest/reporter.php';

//
require_once('session_data_db.inc');
require_once("f_mysql.inc");
require_once('tokenizer.inc');

class session_data_db_T extends UnitTestCase
{
  public function __construct()
  {
    $this->UnitTestCase();
  }

  public function test()
  {
    $obj = new session_data_db();

    // �Ȥꤢ����DB�ϥ�ɥ�Ϥͤ�
    $dbh = new dbh_mysql;
    $dbh->set_user("root");
    $dbh->set_pass("");
    $dbh->set_database_name("test");
    $dbh->set_host_name("localhost");
    $dbh->connect(); // �����Υ��顼�����å��Ͼ�ά����衩
    $obj->set_db($dbh);

    // �������餬�ƥ��ȡ�
    // �ޤ������̤˥ǡ����ͤù���
    $obj->set_id( tokenizer::get() );

    //
    $this->assertIdentical($obj->read(), false);

    //$this->assertIdentical($obj->fix_session(), true);
    $ret = $obj->fix_session();
//var_dump($ret);
    $this->assertIdentical($ret, true);


    // �ǡ�����­������
    $this->assertIdentical($obj->add("test1","value1-1"), true);
    $this->assertIdentical($obj->add("test1","value1-2"), true);
    $this->assertIdentical($obj->add("test1","value1-3"), true);
    $this->assertIdentical($obj->add("test2","value2"), true);
    $this->assertIdentical($obj->add("test","value"), true);

    // �񤭹���
    $this->assertIdentical($obj->write(), true);

    // ��ʣ�����񤭹��ߤζػ�
    $this->assertIdentical($obj->fix_session(), false);

    // ����
    $this->assertIdentical($obj->find("test"), "value");
    $this->assertIdentical($obj->find("test2"), "value2");

    // ����Ū����
    $awk = $obj->find_array("test1");
    $twk = array_diff($awk, array("value1-1", "value1-2", "value1-3"));
    $this->assertIdentical($twk, array());

    // ʸ����μ���������
    $obj2 = new session_data_db();
    $obj2->set_db($dbh);
    $obj2->set_id( $obj->get_id() );
    $this->assertIdentical($obj2->read(), true);

    // �⤦�����󸡺�
    $this->assertIdentical($obj2->find("test"), "value");
    $this->assertIdentical($obj2->find("test2"), "value2");

    // ����Ū����
    $awk = $obj2->find_array("test1");
    $twk = array_diff($awk, array("value1-1", "value1-2", "value1-3"));
    $this->assertIdentical($twk, array());

    // ���
    $obj2->del();
    $this->assertIdentical($obj2->is_session(), false);
  }
}

$test = new session_data_db_T;
$test->run(new TextReporter());

