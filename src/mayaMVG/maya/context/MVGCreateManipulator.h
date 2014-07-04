#pragma once

#include <maya/MPxManipulatorNode.h>
#include "mayaMVG/maya/context/MVGManipulatorUtil.h"
#include "mayaMVG/core/MVGMesh.h"
#include "mayaMVG/core/MVGCamera.h"
#include <map>

namespace mayaMVG {

class MVGContext;

class MVGCreateManipulator: public MPxManipulatorNode
{
    enum SelectionState {
        SS_NONE = 0
        , SS_POINT
        , SS_EDGE
    };

	public:
		MVGCreateManipulator();
		virtual ~MVGCreateManipulator();
		
	public:
		static void * creator();
		static MStatus initialize();

	public:
		virtual void postConstructor();
		virtual void draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStatus);
		virtual MStatus doPress(M3dView &view);
		virtual MStatus doRelease(M3dView &view);
		virtual MStatus doMove(M3dView &view, bool& refresh);
		virtual MStatus doDrag(M3dView& view);
		virtual void preDrawUI(const M3dView&);
		virtual void drawUI(MHWRender::MUIDrawManager&,	const MHWRender::MFrameContext&) const;

	public:
		void setContext(MVGContext* ctx);

	private:
		MVGManipulatorUtil::DisplayData* getCachedDisplayData(M3dView& view);
				
		void drawPreview2D(M3dView& view, MVGManipulatorUtil::DisplayData* data);

	public:
		static MTypeId _id;
		std::map<std::string, MVGManipulatorUtil::DisplayData> _cache; //FIXME use caching on the wrapper side
		SelectionState _selectionState;
        MVGContext* _ctx;
};

} // namespace