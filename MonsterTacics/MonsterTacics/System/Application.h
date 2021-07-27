#pragma once
#include <memory>

class SceneController;
struct Size;


// 表示すべき画面の情報を持つ
class Viewport
{
public:
	Size GetSize()const;
};

/// <summary>
/// Application(シングルトンクラス)
/// main関数から呼ばれるただ一つのクラス
/// ゲームの初期化、起動、終了処理を行う。
/// ゲームが始まって終わるまで共通で使用する要素を
/// このクラスの持ち物とする
/// </summary>
class Application
{
private:
	// 生成禁止
	Application();

	// コピー、代入禁止
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	std::unique_ptr<SceneController> sceneController_;
	Viewport viewport_;
public:
	static Application& Instance();

	~Application();

	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(void);

	/// <summary>
	/// ゲーム起動
	/// </summary>
	void Run(void);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Terminate(void);

	/// <summary>
	/// アプリケーションを終了する
	/// </summary>
	void Exit(void);

	const Viewport& GetViewport()const;
};