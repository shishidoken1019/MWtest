<?php

/**
 * MVC Model部分基底クラス
 *
 * 少しだけお便利げに作る。MVCのMを担当
 * skeltonからの追加は以下の通り
 * ・DB handle
 * ・Logクラス各種
 * ・convインスタンス取得
 * ・
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model_skeleton.inc');
require_once('db_manager.inc');
require_once('log.inc');
require_once('log_dummy.inc');
require_once('file_util.inc');
require_once('conv_util.inc');
require_once('is.inc');
require_once('secure_conv.inc');

abstract class base_model extends base_model_skeleton {

//public:

//
public function __construct() {
  parent::__construct();
  // $this->init(); 上位で叩いているはずなので
}
//
public function init()
{
  parent::init();
}

//
//public function set_tmp_filename($s) { $this->set_bag('tmp_filename', $s); }
//public function get_tmp_filename() { return $this->get_bag('tmp_filename'); }

/**
 * DBハンドル取得
 *
 * DBハンドルを取得する。
 * 未接続の場合、接続してから取得する。
 *
 * @access public
 * @return object DBハンドル
 */
public function get_db()
{
  // 未接続なら接続しとけや
  if ( false === $this->is_bag('dbh') ) {
    $this->set_bag('dbh', db_manager::get_handle( $this->get_config() ));
  }

  // ハンドルを復帰
  return $this->get_bag('dbh');
}

/**
 * CONVインスタンス取得
 *
 * デフォはf_convだが、configに記述があれば違うインスタンスに
 *
 * @access public
 * @return object convインスタンス
 */
public function get_conv()
{
//print "in to get_conv \n";
  if (false === $this->is_bag('conv')) {
//print "new create conv \n";

    if ('secure_conv' === $this->get_config()->find('template_engine')) {
      $this->set_bag('conv', new secure_conv);
    } else 
    if ('smarty' === $this->get_config()->find('template_engine')) {
      require_once('mw_smarty.inc');
      $this->set_bag('conv', new mw_smarty);
    } else
    if ('' === $this->get_config()->find('template_engine')) {
      $this->set_bag('conv', new f_conv);
    } else {
      $cn = $this->get_config()->find('template_engine');
//var_dump($cn);
      $this->set_bag('conv', new $cn);
    }

    // Smarty系の場合の追加処理
    $cn = get_class($this->get_bag('conv'));
    if (false !== (stristr($cn, 'smarty'))) {
      $this->get_bag('conv')->template_dir = $this->get_config()->find('template_dir');
      if ("" !== ($s = $this->get_config()->find('smarty_compile_dir'))) {
        $this->get_bag('conv')->compile_dir = $s;
      }
      if ("" !== ($s = $this->get_config()->find('smarty_config_dir'))) {
        $this->get_bag('conv')->config_dir = $s;
      }
    }

    // 必要なconfig設定の追加
    $this->get_bag('conv')->monoDic('uri', $this->get_config()->find('uri'));
    $this->get_bag('conv')->monoDic('ssl_uri', $this->get_config()->find('ssl_uri'));
    $this->get_bag('conv')->monoDic('mx_domain', $this->get_config()->find('mx_domain'));

    $mobj = $this->get_mobile();
    $sp = new simple_put;
    if (true === $mobj->is_docomo()) {
      $this->get_bag('conv')->multiDic('is_docomo', $sp);
    } else
    if (true === $mobj->is_au()) {
      $this->get_bag('conv')->multiDic('is_au', $sp);
      $this->get_bag('conv')->multiDic('is_ez', $sp);
    } else
    if (true === $mobj->is_softbank()) {
      $this->get_bag('conv')->multiDic('is_softbank', $sp);
    }
  }
  //
  return $this->get_bag('conv');
}

/**
 * body自動作成 with conv
 *
 * $thisのconvインスタンスと設定ファイルのtemplate_dir内にある
 * 引数テンプレートファイルを使ってbodyを自動作成する
 * 引数なし(又は空文字)の場合、mapファイルに設定されたtemplateが有効になる
 * 「ぢつはこのメソッドcallしなくてもいいじゃん」とか気づいちゃだめｗ
 *
 * @access protected
 * @param string $tmp_filename テンプレートファイル名
 * @return boolean なにか問題あったらfalse
 */
public function make_body_with_conv($tmp_filename = "")
{
  if ("" !== $tmp_filename) {
    $this->set_tmp_filename($tmp_filename);
  }
//var_dump($this->get_tmp_filename());
  //$this->set_body($this->get_conv()->conv(file_util::read_file($this->get_config()->find("template_dir") . $tmp_filename)));

  return true;
}

/**
 * エラーログ用logクラスインスタンス取得
 *
 * @access public
 * @return object logインスタンス エラーの場合はnull
 */
public function get_error_log() { return $this->_get_log('error'); }

/**
 * warningログ用logクラスインスタンス取得
 *
 * @access public
 * @return object logインスタンス エラーの場合はnull
 */
public function get_warning_log() { return $this->_get_log('warning'); }

/**
 * debugログ用logクラスインスタンス取得
 *
 * @access public
 * @return object logインスタンス エラーの場合はlog_dummyインスタンス
 */
public function get_debug_log() { return $this->_get_log('debug'); }

//
protected function _get_log($s)
{
  // 設定が足りなきゃdummy return 
  $s = $this->get_config()->find($s . '_log_path');
  if ("" === $s) {
    $obj = new log_dummy;
    $this->set_bag($s . '_log', $obj);
    return $this->get_bag($s . '_log');
  }

  //
  if (false === $this->is_bag($s . '_log')) {
//print "new create error_log \n";
    $obj = new log;
    //$obj->set_filename($s);
    $obj->set_rotate_filename($s);
    $obj->set_pname($this->get_my_name());
    $this->set_bag($s . '_log', $obj);
  }
  //
  return $this->get_bag($s . '_log');

}

/*
// ログ関連クラスの登録
protected function _get_log($type)
{
  if (isset($this->log_[$type])) {
    // インスタンスが作れ泣ければfalse
$type . "_log"
  }
  // 設定
$type . "_log_mode"
$type . "_log_spreadtime"

}
*/


//private:
} // end of class


