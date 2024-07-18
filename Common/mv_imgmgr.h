#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

class ImageManager {		//图像管理器
public:

	~ImageManager()
	{
		m_images.clear();
	}
	inline bool ExistImage(const string& name) const
	{
		return m_images.find(name) != m_images.end();
	}
	PIMAGE GetImage(const string& name)
	{
		if (!ExistImage(name))
		{
			ErrorLogTip("不存在名为\"" + name + "\"的图片！", "ImageManager::GetImage");
			return nullptr;
		}
		return m_images[name];
	}
	static string GetImageFullPath(const string& filename)
	{
		string path;
		if (ExistFile(path = ASSETS_DIR + filename))
			return path;
		if (ExistFile(path = COMMON_DIR + filename))
			return path;
		if (ExistFile(filename))
			return filename;
		ErrorLogTip("无法获取图像全路径, 文件名为 \"" + filename + "\"", "ImageManager::GetImageFullPath");
		return "";
	}
	void AddImage(const string& path, const string& name)
	{
		PIMAGE pimg = newimage();
		getimage(pimg, path.c_str());
		m_images.insert(make_pair(name, pimg));
	}
	void AddImage(const string& name)
	{
		string path{ GetImageFullPath(name) };
		if (path.empty())
			return;
		AddImage(path, name);
	}
	inline void AddImages(vector<string>&& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void AddImages(const vector<string>& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void AddImages(initializer_list<string>&& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void ClearImages()
	{
		m_images.clear();
	}
private:
	map<string, PIMAGE> m_images;

}imgMgr;