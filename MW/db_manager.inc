<?php

/**
 * DBマネージャクラス
 *
 * いわゆる ファクトリー
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('config.inc');
require_once('db_handle_maps.inc');

class db_manager
{

/**
 * DBハンドル取得
 *
 * 実際には引数の型に応じて振り分ける
 *
 * @access public
 * @param string|object $param stringまたはconfigオブジェクトのパラメタ
 * @return db_handle_object DBハンドル(群)オブジェクト
 */
static public function get_handle($param)
{
  // 文字列ならおそらくファイル名であろうと見なす
  if (true === is_string($param)) {
    return db_manager::_get_handle_mono($param);
  }

  // else
  // config objectとみなして処理
  // mono系として設定があれば
  $s = $param->find('db_config_path');
  if ('' !== $s) {
    // mono系として処理して終了
    return db_manager::_get_handle_mono($s);
  }

  // else
  // XXX クラスタリング系処理
  if (true === $param->is('db_clustering')) {
    // XXX
    $obj = new db_handle_maps;
    $obj->set_config($param);
    return $obj;
  }

  // else
  // なんもないやん
  return null;
}

// とりあえずconfig系を想定。XMLとか出来たら適当にまとめなおし
static public function _get_handle_mono($config_filename)
{
  // 一応チェック
  if(false === file_exists($config_filename)){
    return null;
  }

  // 取り込み
  $conf = new config;
  $conf->set_file($config_filename);

  // DBMSのチョイス
  $dbms = $conf->find('type');
  if ((!(strcasecmp($dbms, "postgresql")))||(!(strcasecmp($dbms, "pgsql")))) {
//print "Trap 1\n";
    require_once('f_pgsql.inc');
    $conn = new dbh_pgsql;
  } else
  if (!(strcasecmp($dbms, "mysql"))) {
//print "Trap 2\n";
    require_once('f_mysql.inc');
    $conn = new dbh_mysql;
  } else
  {
//print "Trap 3\n";
    // 判別不能なのでエラー復帰
    return null;
  }

  // 設定
  $conn->set_user($conf->find('user'));
  $conn->set_pass($conf->find('pass'));
  $conn->set_database_name($conf->find('database'));
  $conn->set_host_name($conf->find('host'));
  $conn->set_port_num($conf->find('port'));

//print "Trap1\n";
  // 接続
  // XXX 一応再帰系にしとく〜
  if (false == $conn->rconnect()) {
//print "Trap2\n";
//print $conn->get_error_message() . "\n";
    return null;
  }
//print "Trap3\n";

  // XXX 一応パスワード情報だけ消しとく
  $conn->set_pass('----');

  // 復帰
  return $conn;
}

} // end of class


