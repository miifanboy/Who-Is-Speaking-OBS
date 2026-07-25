//
// Created by eren on 25/07/2026.
//

#include "WISDisplay.h"

#include <QWindow>

OBSRenderWidget::OBSRenderWidget(QWidget *parent) : QWidget(parent) {
	// 1. Tell Qt that this widget paints directly to the screen/GPU
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_OpaquePaintEvent, true);

	// 2. Ensure the widget has a valid native window handle
	setAttribute(Qt::WA_DontCreateNativeAncestors, true);
	setAttribute(Qt::WA_NativeWindow, true);
}

OBSRenderWidget::~OBSRenderWidget() {
	// Prevent memory leaks by explicitly destroying the display context
	if (obsDisplay) {
		obs_display_destroy(obsDisplay);
	}
}

// Critical: Returning nullptr tells Qt to skip its standard 2D paint engine
QPaintEngine* OBSRenderWidget::paintEngine() const {
	return nullptr;
}

void OBSRenderWidget::paintEvent(QPaintEvent *event) {
	// Intentionally left blank. OBS handles the swapchain presentation.
}
void OBSRenderWidget::CreateOBSDisplay() {
	if (obsDisplay) return;

	// Structure containing the native window handle and sizes
	gs_init_data initData = {};

	// Get the platform-specific window handle from Qt
	initData.window.hwnd = (void*)windowHandle()->winId();
	initData.cx = ;
	initData.cy = height();
	initData.num_backbuffers = 2;
	initData.format = GS_RGBA;

	// Create the display and register the rendering callback
	obsDisplay = obs_display_create(&initData, 0x00000000); // Black background
	if (obsDisplay) {
		obs_display_add_draw_callback(obsDisplay, OBSRenderWidget::RenderCallback, this);
	}
}

void OBSRenderWidget::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event);
	CreateOBSDisplay();
}

void OBSRenderWidget::resizeEvent(QResizeEvent *event) {
	QWidget::resizeEvent(event);
	CreateOBSDisplay();

	// Update the OBS viewport size to match the new widget dimensions
	if (obsDisplay) {
		obs_display_resize(obsDisplay, width(), height());
	}
}

void OBSRenderWidget::RenderCallback(void *data, uint32_t cx, uint32_t cy) {
	// Unused dimensions parameters in this scope
	Q_UNUSED(cx);
	Q_UNUSED(cy);

	// Draw the active video feed (Main Preview) to the active display target
	obs_render_main_texture();
}


