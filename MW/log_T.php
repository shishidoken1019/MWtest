<?php

//
// log���饹(�ƥ���)
//

require_once("./log.php");

// ��������
$log = new log();
$log->set_filename("./test.log"); // ����񤭽Ф��ե�����̾(�ѥ�)
$log->set_pname("winny");         // �ץ����̾

// �ǥե����on�Τ�Τ���
//$log->spreadtime_off();         // off�ʤ饨�ݥå��ǽФ�Ϥ�����
//$log->off();                    // off�ʤ�ե�����˽񤭹��ޤ�ʤ��Ϥ�����

// ����Ĥ������ʤȻפä���...
$log->add("ultra fatal error!");      // �Ĥ���
$log->pause();                        // ���ڤ�������..
$log->add("--");                      // �Ĥ���
$log->add("���򤷤ä���Ĥ���");    // �Ĥ���

//var_dump($log);

$log->flush(); // �ե�����˽񤭽Ф�

// ���Τޤ޼��Υ��˻Ȥ��롣
$log->add("2����");               // �Ĥ���
$log->add(": fatal error.");      // �Ĥ���

$log->flush();


?>
