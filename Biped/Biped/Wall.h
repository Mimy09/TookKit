#pragma once
struct Wall {
public:
	bpd::Point pos; int size;
	bpd::Segment seg1, seg2, seg3, seg4;
	Wall()
		: pos(bpd::Point(0, 0)),
		seg1(bpd::Segment(0, 0, 0, 0)),
		seg2(bpd::Segment(0, 0, 0, 0)),
		seg3(bpd::Segment(0, 0, 0, 0)),
		seg4(bpd::Segment(0, 0, 0, 0)) {
	}
	Wall(bpd::Point point, int sz) {
		pos = point; size = sz;
		seg1 = bpd::Segment(
			point.x - sz, point.y - sz,
			point.x + sz, point.y - sz
		);
		seg2 = bpd::Segment(
			point.x + sz, point.y - sz,
			point.x + sz, point.y + sz
		);
		seg3 = bpd::Segment(
			point.x + sz, point.y + sz,
			point.x - sz, point.y + sz
		);
		seg4 = bpd::Segment(
			point.x - sz, point.y + sz,
			point.x - sz, point.y - sz
		);
	}
	void UpdateColliders() {
		seg1 = bpd::Segment(
			pos.x - size, pos.y - size,
			pos.x + size, pos.y - size
		);
		seg2 = bpd::Segment(
			pos.x + size, pos.y - size,
			pos.x + size, pos.y + size
		);
		seg3 = bpd::Segment(
			pos.x + size, pos.y + size,
			pos.x - size, pos.y + size
		);
		seg4 = bpd::Segment(
			pos.x - size, pos.y + size,
			pos.x - size, pos.y - size
		);
	}
	Wall(const Wall&) {}
	~Wall() {}
};