<?php

/**
 * USER-AGENT�򸫤Ƶ��Ĥ������Ե��Ĥˤ����ꤹ�륯�饹
 *
 * ���ñ�ΤǤ�Ȥ��뤱�ɴ��ܥ���ȥ�����Υ����ȥ����ѤǻȤ���ͤ�
 * �ʲ�����
# �����Ȥ���
@pc
@mobile
@docomo
@softbank
@au
����̾

 *
 *
 *
 *
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('mobile_info.inc');

class user_agent_check {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
}

/**
 * mobile_info���󥹥��󥹤�����
 *
 * @access public
 * @param mobile_info_obj $m mobile_info�Υ��󥹥���
 */
public function set_mobile_obj($m) { $this->mobj_ = $m; }
public function get_mobile_obj() { return $this->mobj_; }

/**
 * ���ĥꥹ�Ȥ�����
 *
 * @access public
 * @param string $s ���ĥꥹ��(���Զ��ڤ�
 */
public function set_arrow_string($s)
{
  return $this->_set_permission_string($s, true);
}

/**
 * ���ݥꥹ�Ȥ�����
 *
 * @access public
 * @param string $s ���ݥꥹ��(���Զ��ڤ�
 */
public function set_denny_string($s)
{
  return $this->_set_permission_string($s, false);
}

/**
 * �᥽�åɤ�����(���)������Ū�˥᥽�å�̾
 *
 * @access protected
 * @param string $s �ꥹ��ʸ����
 * @param boolean $flg true�ʤ���ĥꥹ�ȡ�false�ʤ���ݥꥹ��
 */
protected function _set_permission_string($s, $flg)
{
  // �ޤ����ä�����
  $this->arrow_denny_ = $flg;

//var_dump($s);
  // �Ȥꤢ�������äƤ���ʸ���������ˤ���
  // �����Ƚ�����
  // �ޤ�\r��\n���Ѵ�����
  $s = str_replace(array("\r\n", "\r"), array("\n", "\n"), $s);
  // ������֤�������
  $awk = explode("\n", $s);
//var_dump($awk);

  $this->category_ = array();
  $this->type_ = array();
  // ����ʬ������
  foreach($awk as $line) {
    $line = trim($line);
    if ('' === $line) {
      continue;
    }
    if ('#' === $line[0]) {
      continue;
    }
    //
    if ('@' === $line[0]) {
      $this->category_[] = $line;
    } else {
      $this->type_[] = $line;
    }
  }
//var_dump($this->category_);
//var_dump($this->type_);

  //
  return ;
}

/**
 * Ƚ��
 *
 * @access public
 * @return boolean true�ʤ饢���������ġ�false�ʤ饢�������Բ�
 */
public function is_permission()
{
$ret = "";

  // �ޤ�����
  if (false === empty($this->category_)) {
    foreach($this->category_ as $category) {
      // ��ü�٤ä��٤���
      if ('@docomo' === $category) {
        $wk = $this->mobj_->is_docomo();
      } else
      if ('@ez' === $category) {
        $wk = $this->mobj_->is_ez();
      } else
      if ('@au' === $category) {
        $wk = $this->mobj_->is_ez();
      } else
      if ('@softbank' === $category) {
        $wk = $this->mobj_->is_softbank();
      } else
      if ('@mobile' === $category) {
        $wk = $this->mobj_->is_mobile();
      } else
      if ('@pc' === $category) {
        $wk = !($this->mobj_->is_mobile());
      } else {
        // �񼰤��ѡ�
        $wk = false;
      }

      // Ƚ��
      if (true === $wk) {
        $ret = $this->arrow_denny_;
        break;
      }
    }
  }
  // �ʤˤ��Ҥä����äƤ���
  if ("" !== $ret) {
    return $ret;
  }

  // ����̾����
  if (false === empty($this->type_)) {
    foreach($this->type_ as $type) {
      if ($type === $this->mobj_->get_type()) {
        $ret = $this->arrow_denny_;
        break;
      }
    }
  }
  // �ʤˤ��Ҥä����äƤ���
  if ("" !== $ret) {
    return $ret;
  }

  // �������ä�����ʤ����
  return !($this->arrow_denny_);
}


//private:
private $mobj_;
private $category_;	// @���Ĥ��Ƥ롢����
private $type_;		// ����̾���Τ��
private $arrow_denny_;	// boolean��

} // end of class
