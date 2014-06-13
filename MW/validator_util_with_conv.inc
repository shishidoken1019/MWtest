<?php

/**
 * �Х�ǡ��� util
 * conv�ȷ�ӤĤ��Ƴڡ����顼���̥��å�
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('conv_util.inc');

/*
�ƥ�ץ졼�Ⱦ��

name="hoge" value=%%%hoge%%%

$$$if_error_hoge$$$
�Ȥˤ������顼���ޤ�
$$$/if_error_hoge$$$


$$$if_error_must_hoge$$$
hoge���ʤ�yo ɬ�ܤ����
$$$/if_error_must_hoge$$$

$$$if_error_type_hoge$$$
type���㤲��������ʤ� %%%valid_type_hoge%%%�ʤϤ�������
$$$/if_error_type_hoge$$$

$$$if_error_min_hoge$$$
���ä��㤹���뤫�顪��
����Ǥ� %%%valid_min_hoge%%%���餤���ߤ������顪��
$$$/if_error_min_hoge$$$

$$$if_error_max_hoge$$$
�Ǥ������
�ʤ�ܤʤ�Ǥ� %%%if_error_max_hoge%%%��������Ԥ��᤮������
$$$/if_error_max_hoge$$$

 */

require_once('validator_util.inc');

class validator_util_with_conv extends validator_util {

public function __construct()
{
  //
  parent::__construct();
  // 
  //$this->init();
}

//
public function init()
{
  parent::init();
}

// �������å�
public function set_conv($o) { $this->conv_ = $o; }
public function get_conv() { return $this->conv_; }

// XXX �ѻ�ͽ��
public function set_all_datas()
{
  $conv = $this->get_conv();
  $values = $this->make_all_datas();
  $so = new simple_put;
  foreach ($values as $key => $value) {
    if ($value === true) {
      $conv->multiDic($key, $so);
    } else
    if ($value === false) {
      // �����Ϥʤˤ����ꤷ�ʤ���
      ;
    } else {
      // ���ϥǡ������ݻ�
      // ñ����
      $conv->monoDic($key, $value);
      // checked ��
      conv_util::monoDicChecked($conv, 'checked_' . $key, $value);
      // selected ��
      conv_util::monoDicSelected($conv, 'selected_' . $key, $value);
    }
  }
}

//
public function is_valid()
{
  $ret = parent::is_valid();
//print "with conv ret is ";
//var_dump($ret);
  $conv = $this->get_conv();
  $values = $this->get_value_set_as_a_template();
  $so = new simple_put;
//var_dump($values);

  // ���顼ɽ������Τ�
  if (false === empty($values) ) {
    foreach ($values as $key => $value) {
      if ($value === true) {
//print "$key is true<br>\n";
        $conv->multiDic($key, $so);
      }
    }
  }
  //
  return $ret;
}


//private:
private $conv_;	// conv���󥹥���

} // end of class
