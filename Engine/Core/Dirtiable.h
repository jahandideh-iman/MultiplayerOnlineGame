#pragma  once

namespace mog
{
	class Dirtiable
	{
	public:
		virtual bool isDirty() const { return bIsDirty; }
		virtual void setDirty(bool flag) { bIsDirty = flag; }

	private:
		bool bIsDirty = true;
	};
}