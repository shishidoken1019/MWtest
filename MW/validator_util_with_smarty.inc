<?php

/**
 * �Х�ǡ��� util
 * Smarty�ȷ�ӤĤ��Ƴڡ����顼���̥��å�
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

/*
�ƥ�ץ졼�Ⱦ��

name="hoge" value={$hoge}
{if $if_error_must_hoge == true}
hoge���ʤ�
{/if}
{if $if_error_type_hoge == true}
type���㤦
{/if}
{if $if_error_min_hoge == true} {/if} 
{if $if_error_max_hoge == true} {/if} 

 */

require_once('validator_util.inc');

class validator_util_with_smarty extends validator_util {

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

//
public function set_all_datas()
{
  $smarty = $this->get_smarty();
  $values = $this->make_all_datas();
  foreach ($values as $key => $value) {
    $smarty->assign($key, $value);
  }
}


// �������å�
public function set_smarty($o) { $this->smarty_ = $o; }
public function get_smarty() { return $this->smarty_; }


//private:
private $smarty_;	// smarty���󥹥���

} // end of class
