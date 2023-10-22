
/// ELEMENT EVENTS LIST
/// ////////////////////////////////////////////////////////////////////////////////////////

#include "../utils/asyncTasks.cpp"
#include "elementView.h"

/// TOUCH OVER //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchOverEvent(TouchOverEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchOverEvent()");
  //    auto rem = std::function([]() {});
  addChainFunction(TouchOverEventChain, callBack, removeEventCallBack,
                   TouchOverEventChain == nullptr, false);

  return this;
}

ElementView *ElementView::dispatchTouchOverEvent() {
  if (!this->isMouseOver) {
    this->isMouseOver = true;

    dispatchChainFunction(TouchOverEventChain, this);
  }
  return this;
};

/// TOUCH LEAVE //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchLeaveEvent(TouchLeaveEventType &&callBack,
                                RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchOverEvent()");

  addChainFunction(TouchLeaveEventChain, callBack, removeEventCallBack,
                   TouchLeaveEventChain == nullptr, true);

  return this;
}

ElementView *ElementView::dispatchTouchLeaveEvent() {
  // printf("RUN dispatchTouchLeaveEvent()\n");
  if (this->isMouseOver) {
    this->isMouseOver = false;
    dispatchChainFunction(TouchLeaveEventChain, this);

    for (auto &child : children) {
      child->dispatchTouchLeaveEvent();
    }
  }
  return this;
};

/// TOUCH MOVE //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchMoveEvent(TouchMoveEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchDownEvent()");

  addChainFunction(TouchMoveEventChain, callBack, removeEventCallBack,
                   TouchMoveEventChain == nullptr, true);

  return this;
}

ElementView *ElementView::dispatchTouchMoveEvent(float windowX, float windowY,
                                                 bool isAsync,
                                                 bool useTouchOverChild) {

  //    printf("addContainsFn %.3f %.3f \n",windowX, windowY);
  if (this->contains(windowX, windowY)) {
    this->dispatchTouchOverEvent();

    dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);
    for (auto &child : children) {
      child->dispatchTouchMoveEvent(windowX, windowY);
    }
  }

  return this;
};

/// TOUCH DOWN //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchDownEvent(TouchDownEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchDownEvent()");

  addChainFunction(TouchDownEventChain, callBack, removeEventCallBack,
                   TouchDownEventChain == nullptr, true);

  return this;
}

ElementView *ElementView::dispatchTouchDownEvent(float windowX, float windowY,
                                                 int typeIndex) {
  // printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

  if (this->isMouseOver) {
    dispatchChainFunction(TouchDownEventChain, this, windowX, windowY,
                          typeIndex);

    for (auto &child : children) {
      child->dispatchTouchDownEvent(windowX, windowY, typeIndex);
    }
  }
  return this;
};

/// TOUCH UP //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchUpEvent(TouchUpEventType &&callBack,
                             RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchUpEvent()");

  addChainFunction(TouchUpEventChain, callBack, removeEventCallBack,
                   TouchUpEventChain == nullptr, true);

  return this;
}

ElementView *ElementView::dispatchTouchUpEvent(float windowX, float windowY,
                                               int typeIndex) {
  // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

  if (this->isMouseOver) {
    dispatchChainFunction(TouchUpEventChain, this, windowX, windowY, typeIndex);

    for (auto &child : children) {
      child->dispatchTouchUpEvent(windowX, windowY, typeIndex);
    }
  }
  return this;
};

/// TOUCH ///
template <typename RemoveEventCallBack>
ElementView *
ElementView::addTouchEvent(TouchEventType &&callBack,
                           RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addTouchEvent()");

  addChainFunction(TouchEventChain, callBack, removeEventCallBack,
                   TouchEventChain == nullptr, true);

  return this;
}

ElementView *ElementView::dispatchTouchEvent(float windowX, float windowY,
                                             int typeIndex) {
  // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

  //    if (PositionIsOver(windowX, windowY)) {

  dispatchChainFunction(TouchEventChain, this, windowX, windowY, typeIndex);

  for (auto &child : children) {
    child->dispatchTouchEvent(windowX, windowY, typeIndex);
  }
  //    }

  return this;
};

/// KEY DOWN //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addKeyDownEvent(KeyDownEventType &&callBack,
                             RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addKeyDownEvent()");

  addChainFunction(KeyDownEventChain, callBack, removeEventCallBack,
                   KeyDownEventChain == nullptr, true);
  return this;
}

ElementView *ElementView::dispatchKeyDownEvent(int keyIndex) {

  dispatchChainFunction(KeyDownEventChain, this, keyIndex);

  return this;
};

/// KEY Up //
template <typename RemoveEventCallBack>
ElementView *
ElementView::addKeyUpEvent(KeyUpEventType &&callBack,
                           RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addKeyUpEvent()");

  addChainFunction(KeyUpEventChain, callBack, removeEventCallBack,
                   KeyUpEventChain == nullptr, true);
  return this;
}

ElementView *ElementView::dispatchKeyUpEvent(int keyIndex) {

  dispatchChainFunction(KeyUpEventChain, this, keyIndex);

  return this;
};

/// KEY ///
template <typename RemoveEventCallBack>
ElementView *
ElementView::addKeyEvent(KeyEventType &&callBack,
                         RemoveEventCallBack &&removeEventCallBack) {
  // printf("RUN addKeyDownEvent()");

  addChainFunction(KeyEventChain, callBack, removeEventCallBack,
                   KeyEventChain == nullptr, true);
  return this;
}

ElementView *ElementView::dispatchKeyEvent(int keyIndex) {

  dispatchChainFunction(KeyEventChain, this, keyIndex);

  return this;
}

/// DRAW ///
template <typename RemoveEventCallBack>
ElementView *
ElementView::addDrawEvent(DrawEventType &&callBack,
                          RemoveEventCallBack &&removeEventCallBack) {
  // printf("WINDOW ADD DRAWER\n");

  this->addChainFunction(DrawEventChain, callBack, removeEventCallBack,
                         DrawEventChain == nullptr, false);
  return this;
};

ElementView *ElementView::dispatchDrawEvent(SkCanvas *canvas,
                                            SkPaint *painter) {
  // printf("RUNNNNNNNNN SS2\n");
  this->dispatchChainFunction(DrawEventChain, this, canvas, painter);
  for (auto &child : children) {
    child->dispatchDrawEvent(canvas, painter);
  }
  return this;
};

ElementView *ElementView::draw() {
  return this;
  //    printf("RUNNNNNNNNN SS2\n");
  auto awaitProcess2 = CreateAsyncAwaitGroup();
  //    auto awaitProcess = CreateAsyncAwaitGroup();
  if (this->window == nullptr) {
    std::function<void()> removeEvent = []() {

    };
    this->addMountOnThreeEvent(
        [removeEvent](ElementView *element,
                      ElementView *parentElement) mutable {
          element->dispatchDrawEvent(element->window->surface->getCanvas(),
                                     &element->window->paint);
          //            element->window->refreshFrame();

          removeEvent();
        },
        removeEvent);
  } else {

    this->dispatchDrawEvent(this->window->surface->getCanvas(),
                            &this->window->paint);
    //        this->window->refreshFrame();
  }

  awaitProcess2();
  return this;
};

/// Resize ///
template <typename RemoveEventCallBack>
ElementView *
ElementView::addResizeEvent(ResizeEventType &&callBack,
                            RemoveEventCallBack &&removeEventCallBack) {
  this->addChainFunction(ResizeEventChain, callBack, removeEventCallBack,
                         ResizeEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchResizeEvent(float elementWidth,
                                              float elementHeight) {
  this->dispatchChainFunction(ResizeEventChain, this, elementWidth,
                              elementHeight);

  return this;
};

/// Set Paints ///
template <typename RemoveEventCallBack>
ElementView *
ElementView::addSetPaintsEvent(SetPaintsEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack) {
  addChainFunction(SetPaintsEventChain, callBack, removeEventCallBack,
                   SetPaintsEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchSetPaintsEvent() {
  dispatchChainFunction(SetPaintsEventChain, this);
  return this;
};

/// ADD CHILD
template <typename RemoveEventCallBack>
ElementView *
ElementView::addAddChildEvent(AddChildEventType &&callBack,
                              RemoveEventCallBack &&removeEventCallBack) {

  addChainFunction(AddChildEventChain, callBack, removeEventCallBack,
                   AddChildEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchAddChildEvent(ElementView *newChild) {
  dispatchChainFunction(AddChildEventChain, this, newChild);
  return this;
};

/// REMOVE CHILD
template <typename RemoveEventCallBack>
ElementView *
ElementView::addRemoveChildEvent(RemoveChildEventType &&callBack,
                                 RemoveEventCallBack &&removeEventCallBack) {
  addChainFunction(RemoveChildEventChain, callBack, removeEventCallBack,
                   RemoveChildEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchRemoveChildEvent(int removeIndex, int count) {
  dispatchChainFunction(RemoveChildEventChain, this, removeIndex, count);
  return this;
};

/// REPLACE CHILD
template <typename RemoveEventCallBack>
ElementView *
ElementView::addReplaceChildEvent(ReplaceChildEventType &&callBack,
                                  RemoveEventCallBack &&removeEventCallBack) {
  addChainFunction(ReplaceChildEventChain, callBack, removeEventCallBack,
                   ReplaceChildEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchReplaceChildEvent(int replaceIndex,
                                                    ElementView *oldChild,
                                                    ElementView *newChild) {
  dispatchChainFunction(ReplaceChildEventChain, this, replaceIndex, oldChild,
                        newChild);
  return this;
};

/// SetBackground
template <typename RemoveEventCallBack>
ElementView *ElementView::addSetBackgroundColorEvent(
    SetBackgroundColorEventType &&callBack,
    RemoveEventCallBack &&removeEventCallBack) {
  addChainFunction(SetBackgroundColorEventChain, callBack, removeEventCallBack,
                   SetBackgroundColorEventChain == nullptr, true);
  return this;
};

ElementView *ElementView::dispatchSetBackgroundColorEvent(SkColor newColor) {
  auto asyncAwaitGroup = CreateAsyncAwaitGroup();
  dispatchChainFunction(SetBackgroundColorEventChain, this, newColor);
  asyncAwaitGroup();
  return this;
};

/// MountOnThree
template <typename RemoveEventCallBack>
ElementView *
ElementView::addMountOnThreeEvent(MountOnThreeEventType &&callBack,
                                  RemoveEventCallBack &&removeEventCallBack) {
  //    MountOnThreeEventType chainEl = MountOnThreeEventType(callBack,true);

  MountOnThreeEventChain = MountOnThreeEventChain.CreateNewAfter(callBack, true);
  return this;
};

ElementView *
ElementView::dispatchMountOnThreeEvent(ElementView *parentElement) {
  printf("RUN RUN MOUNT CHAINT\n");

  if (MountOnThreeEventChain != nullptr) {
    MountOnThreeEventChain.callAfter(parentElement);
    //        chainFunc = chainFunc.
    //        chainFunc.c
    //        chainFunc(std::forward<Args>(args)...);
  }
  //    dispatchChainFunction(MountOnThreeEventChain, this, parentElement);
  return this;
};

/// UnmountOnThree
template <typename RemoveEventCallBack>
ElementView *
ElementView::addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack,
                                    RemoveEventCallBack &&removeEventCallBack) {
  addChainFunction(UnmountOnThreeChain, callBack, removeEventCallBack,
                   UnmountOnThreeChain == nullptr, true);
  return this;
};

ElementView *
ElementView::dispatchUnmountOnThreeEvent(ElementView *parentElement) {
  dispatchChainFunction(UnmountOnThreeChain, this, parentElement);
  return this;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
