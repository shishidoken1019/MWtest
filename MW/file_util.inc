<?php

/**
 * �ե������ѥ桼�ƥ���ƥ����饹
 *
 * �ե��������ˤޤĤ��桼�ƥ���ƥ��ϥ��饹
 * �桼�ƥ���ƥ��ϥ��饹�ʤΤǡ�����
 * file_util::�᥽�å�
 * �η����Ǥ�call�����ꤷ�Ƥ���
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

//
class file_util {

// �ե�����ѥ���ֳ�ĥ�Ҥȡס֤���ʳ��פ�ʬ��
// @return array [0]������ʳ���[1]����ĥ��(.�դ�) ��ĥ�ҤϤʤ���ж�ʸ��
static public function split_filename_by_extension($s)
{
$ret = -1;
$wk = 0;

  //
  while( false !== ($wk = strpos($s, '.', $wk))) {
    $ret = $wk;
    $wk ++;
  }

  //
  if (-1 !== $ret) {
    $a[] = substr($s, 0, $ret);
    $a[] = substr($s, $ret);
  } else {
    $a[] = $s;
    $a[] = '';
  }
//var_dump($a);

  //
  return $a;
}

// �ե�����񤭹���
// �����ä���false
static public function add_file($filename, $data)
{
  $fp = @fopen($filename, "a");
  if(!$fp) {
//print "file open error!";
    return false;             // ��λ
  }
  flock($fp, LOCK_EX);        // LOCK_EX => ��¾���å�
  fwrite($fp, $data);
  fclose($fp);
  //
  return true;
}

// �ե�����̾����Υե�������ɤ߹���
static public function read_file($filename)
{
$ret = "";
  //
  if ($fp = @fopen($filename, "r")) {
    // �ե������open�������������ɤ߹���
    while (!feof($fp)) {
      $ret .= fgets($fp);
    }
    @fclose($fp);
  }
  //
  return $ret;
}

// �ե�����򣱹ԣ��ǡ����Ȥ�������ˤȤꤳ���return
static public function read_file_to_array($filename)
{
  $awk = array();
  if ($fp = fopen($filename, 'r')) {
    while (!feof($fp)) {
      $awk[] = trim(fgets($fp));
    }
    fclose($fp);
  }
  //
  return $awk;
}

// �ե�������ɤ߹����EUCʸ�������ɤ��Ѵ�����return
static public function read_file_to_euc($filename)
{
  return
    mb_convert_encoding(file_util::read_file($filename) , "EUC-JP", "auto");
}

// �ե�������ɤ߹����UTF-8ʸ�������ɤ��Ѵ�����return
static public function read_file_to_utf8($filename)
{
  return
    mb_convert_encoding(file_util::read_file($filename) , "UTF-8", "auto");
}

// �ե�������ɤ߹����base64�ˤ���return
static public function read_file_to_base64($filename)
{
  return base64_encode(file_util::read_file($filename));
}


} // end of class
