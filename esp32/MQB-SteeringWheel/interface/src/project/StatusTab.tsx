import { FC } from 'react';

import { Typography } from '@mui/material';


import { WEB_SOCKET_ROOT } from '../api/endpoints';
import { BlockFormControlLabel, FormLoader, MessageBox, SectionContent } from '../components';
import { updateValue, useWs } from '../utils';

import { MQBState } from './types';

export const MQB_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "MQBState";

const LightStateWebSocketForm: FC = () => {
  const { connected, updateData, data } = useWs<MQBState>(MQB_SETTINGS_WEBSOCKET_URL);


  const content = () => {
    if (!connected || !data) {
      return (<FormLoader message="Connecting to WebSocket…" />);
    }
    return (
      <>
        <div>Button State: {data.lastKeyPressed}</div>        
      </>
    );
  };

  return (
    <>
      {content()}
    </>
  );
};



const StatusTab: FC = () => (
  <SectionContent title='Demo Information' titleGutter>
    
    <Typography variant="body1" paragraph>
      MQB State
      <LightStateWebSocketForm/>
    </Typography>
    
  </SectionContent>
);

export default StatusTab;
