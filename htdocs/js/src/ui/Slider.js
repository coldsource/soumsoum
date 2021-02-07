 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {EventsUtils} from '../utils/EventsUtils.js';

export class Slider extends React.Component {
	constructor(props) {
		super(props);
		
		this.delta = 0;
		
		this.ref_rail = React.createRef();
		this.ref_position = React.createRef();
		
		this.beginMove = this.beginMove.bind(this);
		this.endMove = this.endMove.bind(this);
		this.move = this.move.bind(this);
	}
	
	beginMove(e) {
		document.addEventListener('mousemove',this.move);
		document.addEventListener('mouseup',this.endMove);
		
		let height = this.ref_rail.current.offsetHeight;
		this.delta = e.clientY - (1 - this.props.value) * height;
	}
	
	endMove(e) {
		document.removeEventListener('mousemove',this.move);
	}
	
	move(e) {
		let pos = e.clientY - this.delta;
		
		if(pos<0)
			pos = 0;
		
		let height = this.ref_rail.current.offsetHeight;
		if(pos>=height)
			pos = height;
		
		this.props.onChange(EventsUtils.createEvent(this.props.name, 1 - (pos / height)));
	}
	
	render() {
		return (
			<div className="Slider">
				<div ref={this.ref_rail} className="rail">
					<div className="position" ref={this.ref_position} style={{top: (1 - this.props.value) * 100 + '%'}} onMouseDown={this.beginMove}>
						{Math.round(this.props.value*100)}
					</div>
				</div>
			</div>
		);
	}
}
