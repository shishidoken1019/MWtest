<?php

/**
 * ���ӵ������μ���
 *
 * ���������󥹥ȥ饯���˽�����������������
 * ���ȡ����Υ��饹�������󥰥�ȥ�Ǥ⤤���褦�ʡ�
 * �ʲ������ͤˤ���URI
http://www.hajimeteno.ne.jp/i-mode/user_agent.html
http://developers.softbankmobile.co.jp/dp/tool_dl/web/useragent.php
http://www.nttdocomo.co.jp/service/imode/make/content/spec/useragent/index.html
http://www.au.kddi.com/ezfactory/tec/spec/4_4.html

XXX UID�ȵ����ͭ�ֹ����ʪ�äݡ�ξ���������ʤ��Ȥ� orz

 *
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

/*
���ɥ����DoCoMo��i-mode����

�����ȥ�����utn°����Ĥ���ȡ����μ����ֹ���������Ƥ�館�ޤ���
�����������μ����ֹ���������ˡ����μ����ֹ����������ݤ�桼�����˳�ǧ������̤�ɽ�����졢
�桼��������ǧ���̤ǡ�YES�ץܥ���򲡤������Τ߸��μ����ֹ椬��������ޤ���

utn°�����ղäλ���
�㡧
<A href="URL" utn>
<FORM method="�᥽�å�" action="URL" utn>

��������Ƥ�����μ����ֹ�

MOVA
��DoCoMo/1.0/X503i/c10/ser*********** ��
�桼��������������Ȥθ�����ղä�����
ser�θ�������μ����ֹ�

FOMA
��DoCoMo/2.0 YYYY(c10;serXXXXXXXXXXXXXXX; iccxxxxxxxxxxxxxxxxxxxx)��

serXXXXXXXXXXXXXXX
ser��FOMAü�����μ��̻�
iccxxxxxxxxxxxxxxxxxxxx
icc��FOMA�����ɸ��μ��̻�

��AU��ezweb����

AU�ϡ�����Ū�˥��֥����饤��ID��EZ�ֹ�ˤȸƤФ����μ��̻Ҥ�����������Ƥ��ޤ���
�ʤ����������ߥ��֥����饤��ID�Ρ��������롦���ʤ��פ�桼����������Ǥ���褦�ˤʤäƤ��ޤ���

���֥����饤��ID�ϡ��Ķ��ѿ���'HTTP_X_UP_SUBNO'���˼�����Ƥ��ޤ���
perl������$ENV��'HTTP_X_UP_SUBNO'��
PHP������$_SERVER['HTTP_X_UP_SUBNO']

������xxxxxxxxxxxxxx_t*.ezweb.ne.jp

��SOFTBANK�ʥܡ����ե���j-sky����

���եȥХ󥯤ϡ��ѥ��å��̿��б����Τ߸��μ����ֹ������Ǥ��ޤ���

vodafone�ξ�硢���μ����ֹ�ϡ���˥桼��������������Ȥ˴ޤޤ�Ƥ��ޤ���

�桼�����������������
SoftBank/1.0/910T/TJ001/SN Serial Browser/NetFront/3.3 Profile/MIDP-2.0 Configuration/CLDC-1.1
Vodafone/1.0/V802SH/SHJ001[/Serial] Browser/UP.Browser/7.0.2.1 Profile/MIDP-2.0 Configuration/CLDC-1.1 Ext-J-Profile/JSCL-1.2.2 Ext-V-Profile/VSCL-2.0.0
J-PHONE/5.0/V801SH[/Serial] SH/0005aaProfile/MIDP-1.0 Configuration/CLDC-1.0 Ext-Profile/JSCL-1.1.0

/Serial������ʬ�����μ����ֹ�Ȥʤ�ޤ���

����������¤�ֹ�ϥ桼�����桼��ID���Τ����Ф���Ĥ������Τ��ɲä���ޤ���
 */

class mobile_info {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

/**
 * �����
 *
 * ������Ȥ������Ĥļ½������̤ꤳ���Ǥ�äƤ�
 * ����ʬ���Բ�ǽ�ʡ������夲��user-agent�ϰʲ��ΤȤ���

Mozilla/4.0 (compatible; MSIE 6.0; KDDI-HI37) Opera 8.00 [ja]
Mozilla/4.0 (compatible; MSIE 6.0; KDDI-SA39) Opera 8.60 [ja]
Mozilla/4.0 (compatible; MSIE 6.0; KDDI-KC38) Opera 8.50 [ja]
P505i DoCoMo/1.0/P505i/c20/TB/W20H10

 *
 * @access public
 */
public function init()
{
  // �����
  $this->set_sid('');

  // user-agent����
  $ua = getenv('HTTP_USER_AGENT');
//var_dump($ua);
  if (false === $ua) {
// XXX false����ʸ���������false�ˤʤ�äݡ�
//print "getenv false ?\n";
    return false;
  }

  // �ޤ�ʬ��
  $awk = explode('/', $ua);

  // ��¬�Ƚ���
  // ��������ǽи���ǽ����
  if (0 === strncmp('KDDI', $awk[0], 4)) {
    $this->set_carrier(8);
    $this->set_type(substr($awk[0], 5, (strpos($awk[0], ' ') - 5)));
    $this->set_sid(getenv('HTTP_X_UP_SUBNO'));
  } else
  if (0 === strncmp('DoCoMo', $awk[0], 6)) {
    if ('1.0' === $awk[1]) {
      // DoCoMo/1.0/����̾/����å��奵����/���μ��̾���
      $this->set_carrier(1);
      $this->set_type($awk[1]);
      //$this->set_sid();
    } else {
      // DoCoMo/2.0 ����̾ (����å��奵����;���μ��̾���)
      $this->set_carrier(3);
      // ����̾�μ���
      $type = substr($awk[1], 4);
      $pos = strpos($type, '(');
      if (false !== $pos) {
        $type = substr($type, 0, $pos);
      }
      $this->set_type($type);
      //$this->set_sid();
    }
    // i�⡼��ID��������
    $this->set_sid(getenv('HTTP_X_DCMGUID'));
  } else
  if (0 === strncmp('SoftBank', $awk[0], 8)) {
    $this->set_carrier(128 + 1024);
    $this->set_type($awk[2]);
    //$this->set_sid();
    // �����
    // SoftBank/[�֥饦���С������]/[����̾]/[ü���С������]/[ü�����ꥢ���ֹ�]��[�桼������������ȼ���]/[�桼�������������̾]/[�桼������������ȥС������]��[Java����(Profile��/Configuration/)]

    // XXX Ƚ�꼰�����Ϥ���
    // XXX �ʤ�����user-agent�ϰʲ��ΤȤ���
    // SoftBank/1.0/811SH/SHJ001 Browser/NetFront/3.3 Profile/MIDP-2.0 Configuration/CLDC-1.1
    // XXX �Ȥꤢ����̵����ʤΤǤ��Τޤޤˤ��뤱��ɬ�פ˱����ƽ������� orz
//var_dump($awk[4]);
/*
    if ("" !== $awk[4]) {
      if (0 === strncmp('SN', $awk[4], 2)) {
        //
        $aaawk = explode(' ', $awk[4]);
        $this->set_sid($aaawk[0]);
      }
    }
*/
    // XXX ���ä��餷���ä�
    $this->set_sid(getenv('HTTP_X_JPHONE_UID'));
  } else
  if (0 === strncmp('UP.Browser', $awk[0], 10)) {
    $this->set_carrier(8 + 16);
    $pos = strpos($awk[2], '-') + 1;
    $pos2 = strpos($awk[2], ' ');
    $type = substr($awk[2], $pos, ($pos2 - $pos));
    $this->set_type($type);
    $this->set_sid(getenv('HTTP_X_UP_SUBNO'));
  } else
  if (0 === strncmp('Vodafone', $awk[0], 8)) {
    $this->set_carrier(128 + 512);
    $this->set_type($awk[2]);

    // XXX �ʲ��Υ����å��������Ͼ��SoftBank�λ��Υ����å����Ȥ��ơ�
    // XXX �ʲ�����
    // Vodafone/1.0/V705SH/SHJ001 Browser/VF-NetFront/3.3 Profile/MIDP-2.0 Configuration/CLDC-1.1
//var_dump($awk[4]);
/*
    if ("" !== $awk[4]) {
      if (0 === strncmp('SN', $awk[4], 2)) {
        //
        $aaawk = explode(' ', $awk[4]);
        $this->set_sid($aaawk[0]);
      }
    }
*/
    // XXX ���ä��餷���ä�
    $this->set_sid(getenv('HTTP_X_JPHONE_UID'));
  } else
  if (0 === strncmp('J-PHONE', $awk[0], 8)) {
    $this->set_carrier(128 + 256);
    $this->set_type($awk[2]);
    // XXX �ʲ��Υ����å��������Ͼ��SoftBank�λ��Υ����å����Ȥ��ơ�
    // XXX �ʲ�����
    // Vodafone/1.0/V905SH/SHJ001 Browser/VF-NetFront/3.3 Profile/MIDP-2.0 Configuration/CLDC-1.1
//var_dump($awk[4]);
/*
    if ("" !== $awk[3]) {
      if (0 === strncmp('SN', $awk[3], 2)) {
        //
        $aaawk = explode(' ', $awk[3]);
        $this->set_sid($aaawk[0]);
      }
    }
*/
    // XXX ���ä��餷���ä�
    $this->set_sid(getenv('HTTP_X_JPHONE_UID'));
  } else {
//print "$ua \n";
    $this->set_carrier(0);
    $this->set_type("");
    //$this->set_sid();
  }

  //
  return true;
}

//
protected function get_carrier() { return $this->carrier_; }
protected function set_carrier($i) { $this->carrier_ = $i; }

// �ӥåȱ黻�������ؿ�
protected function _is_carrier($i, $j) { return ($i & $j)?true:false; }

/**
 * DoCoMo����ꥢȽ��
 *
 * @access public
 * @return boolean DoCoMo�ϤΥ���ꥢ�ʤ�true
 */
public function is_docomo()
{
  return $this->_is_carrier($this->get_carrier(), 1);
}

/**
 * FOMAȽ��
 *
 * @access public
 * @return boolean FOMA�ʤ�true
 */
public function is_foma()
{
  return $this->_is_carrier($this->get_carrier(), 2);
}

/**
 * EZ����ꥢȽ��
 *
 * @access public
 * @return boolean EZ�ϤΥ���ꥢ�ʤ�true
 */
public function is_ez()
{
  return $this->_is_carrier($this->get_carrier(), 8);
}
public function is_au() { return $this->is_ez(); }

/**
 * HDML�ϵ���Ƚ��
 *
 * @access public
 * @return boolean HDML�Ϥε���ʤ�true
 */
public function is_hdml()
{
  return $this->_is_carrier($this->get_carrier(), 16);
}


/**
 * SoftBank����ꥢȽ��
 *
 * SoftBank��������ؤ�������������!!
 *
 * @access public
 * @return boolean SoftBank�ϤΥ���ꥢ�ʤ�true
 */
public function is_softbank()
{
  return $this->_is_carrier($this->get_carrier(), 128);
}

/**
 * J-PHONEü��Ƚ��
 *
 * @access public
 * @return boolean J-PHONEü���ʤ�true
 */
public function is_terminal_jphone()
{
  return $this->_is_carrier($this->get_carrier(), 256);
}
/**
 * Vodafoneü��Ƚ��
 *
 * @access public
 * @return boolean Vodafoneü���ʤ�true
 */
public function is_terminal_vodafone()
{
  return $this->_is_carrier($this->get_carrier(), 512);
}
/**
 * SoftBankü��Ƚ��
 *
 * @access public
 * @return boolean SoftBankü���ʤ�true
 */
public function is_terminal_softbank()
{
  return $this->_is_carrier($this->get_carrier(), 1024);
}


/**
 * ���Ӥ��ɤ���Ƚ��
 *
 * ���̡�is_docomo()��is_ez��is_softbank��or��
 *
 * @access public
 * @return boolean ���ӷϤʤ�true
 */
public function is_mobile()
{
  $ret = $this->is_softbank() || $this->is_ez() || $this->is_docomo();
  return $ret;
}

//
protected function set_type($s) { $this->type_ = $s; }
/**
 * ����̾����
 *
 * @access public
 * @return string ����̾�������ξ���ʸ��
 */
public function get_type() { return $this->type_; }


// XXX ������
protected function set_sid($s) { $this->sid_ = $s . ''; }
/**
 * ���֥����饤��ID����
 *
 * ����������Ȥ�����
 *
 * @access public
 * @return string ���֥����饤��ID�������ξ���ʸ��
 */
public function get_sid() { return $this->sid_; }

//private:
private $type_;		// ����̾
private $sid_;		// ���֥����饤��ID
private $carrier_;	// ����ꥢ̾���ºݤˤϿ��ͥӥåȤǸ��뤳��
			//   1:DoCoMo
			//   2:FOMA
			//   4:ͽ��
			//   8:au
			//  16:HDMLü��
			//  32:ͽ��
			//  64:ͽ��
			// 128:softbank��
			// 256:J-PHONEü��
			// 512:Vodafoneü��
			//1024:SoftBankü��

} // end of class
