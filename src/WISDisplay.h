//
// Created by eren on 25/07/2026.
//

#ifndef WHO_IS_SPEAKING_OBS_WISDISPLAY_H
#define WHO_IS_SPEAKING_OBS_WISDISPLAY_H
#include <QWidget>
#include <obs.h>

class OBSRenderWidget : public QWidget {
	Q_OBJECT

    public:
	explicit OBSRenderWidget(QWidget *parent = nullptr);
	~OBSRenderWidget();

protected:
	// Core Qt event overrides required for custom rendering
	void moveEvent(QMoveEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	QPaintEngine *paintEngine() const override;

private:
	obs_display_t *obsDisplay = nullptr;
	void CreateOBSDisplay();

	// The static callback function where OBS draws the textures
	static void RenderCallback(void *data, uint32_t cx, uint32_t cy);
};

#endif  //WHO_IS_SPEAKING_OBS_WISDISPLAY_H
